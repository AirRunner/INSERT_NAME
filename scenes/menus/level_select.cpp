#include "level_select.hpp"

class Lesson;

LevelSelect::LevelSelect()
{
    cacheManager = new CacheManager;
    systems::loadJson(doc, "data/lessons/index.json");

    font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    levelSelect = 0;

    cacheManager->audios.load<soundFXLoader>(entt::HashedString{"select"}, "data/sound/select.wav");
    cacheManager->audios.load<soundFXLoader>(entt::HashedString{"back"}, "data/sound/back.wav");

    camera.target = {(float) GetScreenWidth()/2,(float) GetScreenHeight()/2};
    camera.offset = {0,0};
    camera.rotation = 0.f;
    camera.zoom = 1.f;
    
    resetButtons(false);
}
LevelSelect::LevelSelect(CacheManager* cacheManager): cacheManager(cacheManager)
{
    systems::loadJson(doc, "data/lessons/index.json");

    font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    levelSelect = 0;

    cacheManager->audios.load<soundFXLoader>(entt::HashedString{"select"}, "data/sound/select.wav");
    cacheManager->audios.load<soundFXLoader>(entt::HashedString{"back"}, "data/sound/back.wav");

    camera.target = {(float) GetScreenWidth()/2,(float) GetScreenHeight()/2};
    camera.offset = {0,0};
    camera.rotation = 0.f;
    camera.zoom = 1.f;
    
    resetButtons(false);
}

Scene* LevelSelect::handleEvents(float deltaTime)
{
    if(WindowShouldClose())
    {
        delete this;
        return nullptr;
    }
    if(IsKeyPressed(KEY_F11))
    {
        systems::toggleFullscreen();
        camera.target = {(float) GetScreenWidth()/2,(float) GetScreenHeight()/2};
        if(doc.IsArray()) //the world select part
        {
            resetButtons(false);
        }
        else //the level select part
        {
            resetButtons(true);
        }
    }

    if(IsKeyPressed(KEY_UP))
    {
        levelSelect--;
        PlaySound(cacheManager->audios.handle(entt::HashedString{"select"})->audio);
    }
    if(IsKeyPressed(KEY_DOWN))
    {
        levelSelect++;
        PlaySound(cacheManager->audios.handle(entt::HashedString{"select"})->audio);
    }

    Vector2 newMousePos = GetMousePosition();
    if(Vector2Distance(mousePos, newMousePos))
    {
        mousePos = newMousePos;
        mouseActive = true;
    }
    else
    {
        mouseActive = false;
    }

    //camera.offset.y += GetMouseWheelMove()*50;

    //int height = GetScreenHeight();
    //int heightBox = 50;
    //int padding = 30;
    //if(-(((int)size-1)*(heightBox+padding)+ padding) - (heightBox + padding)+ height < 0)
    //{
    //    if(camera.offset.y > 0)
    //    {
    //        camera.offset.y = 0;
    //    }
    //    else if(camera.offset.y < -(((int)size-1)*(heightBox+padding)+ padding) - (heightBox + padding)+ height)
    //    {
    //        camera.offset.y = -(((int)size-1)*(heightBox+padding)+ padding) - (heightBox + padding)+ height;
    //    }
    //}

    if(IsKeyPressed(KEY_ESCAPE))
    {
        PlaySound(cacheManager->audios.handle(entt::HashedString{"back"})->audio);
        systems::loadJson(doc, "data/lessons/index.json");
        levelSelect = 0;
        resetButtons(false);
    }
    
    if(IsKeyPressed(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && systems::checkCollisionMouseButtons(registry, mousePos)))
    {
        PlaySound(cacheManager->audios.handle(entt::HashedString{"select"})->audio);
        if(doc.IsArray()) //the world select part
        {
            systems::loadJson(doc, doc[levelSelect]["index"].GetString());
            levelSelect = 0;
            resetButtons(true);
        }
        else //the level select part
        {
            delete this;
            return new Lesson(doc["levels"][levelSelect]["path"].GetString());
        }
    }

    return this;
}

Scene* LevelSelect::update(float deltaTime)
{
    if(levelSelect < 0)
    {
        levelSelect = (int) size -1;
    }
    else if(levelSelect >= (int) size)
    {
        levelSelect = 0;
    }
    systems::updatePos(registry, deltaTime);
    levelSelect = systems::updateButtons(registry, mousePos, mouseActive, levelSelect);
    return this;
}

void LevelSelect::render() const
{
    float fontSize = 40;
    float spacing = 0;

    systems::drawEntities(registry);

    BeginMode2D(camera);
        systems::drawButtons(registry, font, fontSize, spacing);
    EndMode2D();
}

LevelSelect::~LevelSelect()
{
    UnloadFont(font);
}

void LevelSelect::resetButtons(bool level)
{
    auto view = registry->view<button>();
    for(auto entity : view)
    {
        registry->destroy(entity);
    }

    if(level)
    {
        size = doc["levels"].Size();
    }
    else
    {
        size = doc.Size();
    }

    int width = screenWidth;
    int widthBox = 500;
    int heightBox = 65;
    int padding = 30;
    for(rj::SizeType i = 0; i < size; ++i)
    {
        auto entity = registry->create();
        auto& btn = registry->assign<button>(entity);
        btn.rect.x = width/2 - widthBox/2;
        btn.rect.y = (heightBox+padding)*i + padding;
        btn.rect.width = widthBox;
        btn.rect.height = heightBox;
        if(level)
        {
            btn.text = doc["levels"][i]["name"].GetString();
        }
        else
        {
            btn.text = doc[i]["name"].GetString();
        }
        btn.selected = false;
        btn.color = BLACK;
        btn.id = i;
    }
}
