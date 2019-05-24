#include "text_editor.hpp"

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Werror"
// #pragma GCC diagnostic pop

TextEditor::TextEditor()
{
	font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 40, NULL, 600);

	float width = 1280;
    float height = 720;
    float padding = 50;
    rect =
    {
        padding,
        height-(height)/3+padding,
        width-2*padding,
        height/3 - 2*padding
    };

    text = new char[10000];
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
	delete text;
}
