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
            int posY = registry->get<position>(selectedTool).y;
            switch (posY) {    // Positions of the 6 buttons on the y axis
                case 135:
                    systems::loadJson(doc, "data/lessons/visual/tools/variable.json");
                    break;
                case 300:
                    systems::loadJson(doc, "data/lessons/visual/tools/pointer.json");
                    break;
                case 465:
                    systems::loadJson(doc, "data/lessons/visual/tools/char2.json");
                    break;
                case 630:
                    systems::loadJson(doc, "data/lessons/visual/tools/char3.json");
                    break;
                case 795:
                    systems::loadJson(doc, "data/lessons/visual/tools/char4.json");
                    break;
                case 960:
                    systems::loadJson(doc, "data/lessons/visual/tools/char7.json");
                    break;
                default:
                    systems::loadJson(doc, "data/lessons/visual/tools/variable.json");
                    std::cout << posY << " : default" << std::endl;
                    break;
            }
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
    /*systems::updateAnims(registry, 3, deltaTime);
    animManager.udpateAnims(deltaTime);*/
    return this;
}

void VisualEditor::render() const
{
    DrawRectangle(1545, 0, 375, 1080, DARKGRAY);
    systems::drawEntities(registry);
}

VisualEditor::~VisualEditor()
{

}
