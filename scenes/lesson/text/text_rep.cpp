#include "text_rep.hpp"


TextRep::TextRep()
{

}

Scene* TextRep::handleEvents(float deltaTime)
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

Scene* TextRep::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    return this;
}

void TextRep::render() const
{
    BeginDrawing();

    systems::drawEntities(registry);

    ClearBackground(WHITE);

    DrawFPS(0,0);

    DrawText("TEST", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

}

TextRep::~TextRep()
{

}
