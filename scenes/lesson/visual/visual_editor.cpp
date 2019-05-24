#include "visual_editor.hpp"
#include "../menus/pause_menu.hpp"


VisualEditor::VisualEditor()
{
    cacheManager = new CacheManager;
    systems::loadJson(doc, "data/lessons/visual/visual.json");
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
    if(IsKeyPressed(KEY_ESCAPE))
    {
        return new PauseMenu(this, this->cacheManager);
    }
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedSprite = systems::checkCollisionMouseSprite(registry, mousePos);
        selectedTool = systems::checkCollisionMouseTool(registry, mousePos);
        if (registry->valid(selectedTool)) {
            // For the moment it can only load variables
            systems::loadJson(doc, "data/lessons/visual/tools/variable.json");
            parser.parseVisual(*this);
            systems::drawEntities(registry);
        }
    }
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (registry->valid(selectedSprite)) {
            Vector2 distance = Vector2Subtract(mousePos, GetMousePosition());
            auto currPos = registry->get<position>(selectedSprite);
            registry->replace<position>(selectedSprite, currPos.x -= distance.x, currPos.y -= distance.y);
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
}

VisualEditor::~VisualEditor()
{

}
