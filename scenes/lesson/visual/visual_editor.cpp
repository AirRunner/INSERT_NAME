#include "visual_editor.hpp"


VisualEditor::VisualEditor()
{
    cacheManager = new CacheManager;
    systems::loadJson(doc, "data/lessons/visual/visual.json");
    font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    parser.parseVisual(*this);
}

Scene* VisualEditor::handleEvents(float deltaTime)
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
    
    Vector2 newMousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedEntity = systems::checkCollisionMouseSprite(registry, mousePos);
    }
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 distance = Vector2Subtract(mousePos, newMousePos);
        if (registry->valid(selectedEntity)) {
            auto currPos = registry->get<position>(selectedEntity);
            registry->replace<position>(selectedEntity, currPos.x -= distance.x, currPos.y -= distance.y);
        }
    }

    return this;
}

Scene* VisualEditor::update(float deltaTime)
{
    mousePos = GetMousePosition();
    systems::updatePos(registry, deltaTime);
    return this;
}

void VisualEditor::render() const
{
    DrawRectangle(1030, 0, 250, 720, DARKGRAY);
    systems::drawEntities(registry);
    systems::drawButtons(registry, font, 40, 0);
}

VisualEditor::~VisualEditor()
{

}
