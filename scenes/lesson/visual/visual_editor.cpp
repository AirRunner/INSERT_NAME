#include "visual_editor.hpp"


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
    
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && systems::checkCollisionMouseSprite(registry, mousePos)) {
        registry->view<position>().each([mousePos](auto entity, auto& position)
            {
                position.x = mousePos.x;
                position.y = mousePos.y;
            }
        );
    }

    return this;
}

Scene* VisualEditor::update(float deltaTime)
{
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
