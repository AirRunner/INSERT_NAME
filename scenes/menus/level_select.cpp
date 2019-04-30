#include "level_select.hpp"

class Lesson;

LevelSelect::LevelSelect()
{
    systems::loadJson(doc, "../data/lessons/index.json");

    font = LoadFontEx("../data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    levelSelect = 0;

    camera.target = {1280/2,720/2};
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
    if(IsKeyPressed(KEY_F10))
    {
        ToggleFullscreen();
    }

    if(IsKeyPressed(KEY_UP))
    {
        levelSelect--;
    }
    if(IsKeyPressed(KEY_DOWN))
    {
        levelSelect++;
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

    camera.offset.y += GetMouseWheelMove()*50;

    if(camera.offset.y > 0)
    {
        camera.offset.y = 0;
    }
    else if(camera.offset.y < -(((int)size-1)*150 + 30) - 150 + 720)
    {
        camera.offset.y = -(((int)size-1)*150 + 30) - 150 + 720;
    }

    if(IsKeyPressed(KEY_ESCAPE))
    {
        systems::loadJson(doc, "../data/lessons/index.json");
        levelSelect = 0;
        resetButtons(false);
    }
    
    if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
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
        levelSelect = 0;
    }
    else if(levelSelect >= (int) size)
    {
        levelSelect = (int) size -1;
    }
    systems::updatePos(registry, deltaTime);
    levelSelect = systems::updateButtons(registry, mousePos, mouseActive, levelSelect);
    return this;
}

void LevelSelect::render() const
{
    float fontSize = 40;
    float spacing = 0;
    BeginDrawing();

    ClearBackground(BLACK);

    systems::drawEntities(registry);

    BeginMode2D(camera);
        systems::drawButtons(registry, font, fontSize, spacing);
    EndMode2D();

    EndDrawing();
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

    int width = 1280;
    int widthBox = 500;
    int heightBox = 120;
    for(rj::SizeType i = 0; i < size; ++i)
    {
        auto entity = registry->create();
        auto& btn = registry->assign<button>(entity);
        btn.rect.x = width/2 - widthBox/2;
        btn.rect.y = (heightBox+30)*i + 30;
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
