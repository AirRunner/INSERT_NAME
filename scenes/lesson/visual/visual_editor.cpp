#include "visual_editor.hpp"


VisualEditor::VisualEditor()
{

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

    return this;
}

Scene* VisualEditor::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    return this;
}

void VisualEditor::render() const
{
    systems::drawEntities(registry);

    DrawText("TEST", 190, 200, 20, LIGHTGRAY);
}

VisualEditor::~VisualEditor()
{

}
