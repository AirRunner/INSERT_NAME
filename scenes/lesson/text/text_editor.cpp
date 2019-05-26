#include "text_editor.hpp"

TextEditor::TextEditor()
{
	font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 30, NULL, 600);

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

    file = 0;
    droppedFiles = { 0 };

    // interp = new cling::Interpreter(0, nullptr, LLVMDIR);
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
    if (IsFileDropped() && !file)
    {
        droppedFiles = GetDroppedFiles(&file);
        // cling::Interpreter::loadHeader(droppedFiles[0], Transaction **T=0);
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

    if (!file) DrawTextEx(font, "Drop your file to this window!", {100,40}, 30, 0, LIGHTGRAY);
    else
    {
    	DrawTextEx(font, "Dropped file:", {100,40}, 30, 0, LIGHTGRAY);

        if(file)
        {
            DrawRectangle(0, 85, 1280, 60, Fade(LIGHTGRAY, 0.5f));

            DrawTextEx(font, droppedFiles[0], {120,100}, 30, 0, LIGHTGRAY);
        }
    }
}

TextEditor::~TextEditor()
{
	ClearDroppedFiles();
}
