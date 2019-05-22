#include "text_editor.hpp"

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Werror"
#include "../../../systems/raygui.h"
// #pragma GCC diagnostic pop

TextEditor::TextEditor()
{
	font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 40, NULL, 600);

}

Scene* TextEditor::handleEvents(float deltaTime)
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

Scene* TextEditor::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    return this;
}

void TextEditor::render() const
{
    systems::drawEntities(registry);

    DrawText("TEST", 190, 200, 20, LIGHTGRAY);
}

TextEditor::~TextEditor()
{

}
