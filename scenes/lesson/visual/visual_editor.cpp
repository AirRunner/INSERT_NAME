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
    BeginDrawing();

    systems::drawEntities(registry);

    ClearBackground(WHITE);

    DrawFPS(0,0);

    DrawText("TEST", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

}

VisualEditor::~VisualEditor()
{

}
