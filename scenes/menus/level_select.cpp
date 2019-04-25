#include "level_select.hpp"

class Lesson;

LevelSelect::LevelSelect()
{
    std::ifstream ifs("../data/lessons/index.json");
    rj::IStreamWrapper isw(ifs);
    doc.ParseStream(isw);

    font = LoadFontEx("../data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    levelSelect = 0;
    
    resetButtons();
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
    
    if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if(assert(doc.IsArray())) //the world select part
        {
            std::ifstream ifs(doc[levelSelect]["index"].GetString());
            rj::IStreamWrapper isw(ifs);
            doc.ParseStream(isw);
            resetButtons();
        }
        else //the level select part
        {
            delete this;
            return new Lesson(doc["levels"][levelSelect].GetString());
        }
    }

    return this;
}

Scene* LevelSelect::update(float deltaTime)
{
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

void LevelSelect::resetButtons()
{
    auto view = registry->view<button>();
    registry->destroy(view.begin(), view.end());
    for(rj::SizeType i = 0; i < doc.Size(); ++i)
    {
        auto entity = registry->create();
        auto& btn = registry->assign<button>(entity);
        btn.rect.x = 50;
        btn.rect.y = 150*i + 50;
        btn.rect.width = 500;
        btn.rect.height = 120;
        btn.text = doc[i]["name"].GetString();
        btn.selected = false;
        btn.color = BLACK;
        btn.id = i;
    }
}
