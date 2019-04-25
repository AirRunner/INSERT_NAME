#include "level_select.hpp"

class Lesson;

LevelSelect::LevelSelect()
{
    systems::loadJson(doc, "../data/lessons/index.json");

    font = LoadFontEx("../data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    levelSelect = 0;
    
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
    else if(levelSelect > (int) size)
    {
        levelSelect = (int) size;
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
    systems::drawButtons(registry, font, fontSize, spacing);

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

    for(rj::SizeType i = 0; i < size; ++i)
    {
        auto entity = registry->create();
        auto& btn = registry->assign<button>(entity);
        btn.rect.x = 50;
        btn.rect.y = 150*i + 50;
        btn.rect.width = 500;
        btn.rect.height = 120;
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
