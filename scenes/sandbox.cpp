#include "sandbox.hpp"


Sandbox::Sandbox()
{

}

Scene* Sandbox::handleEvents(float deltaTime)
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

Scene* Sandbox::update(float deltaTime)
{

    return this;
}

void Sandbox::render() const
{
    BeginDrawing();

    ClearBackground(WHITE);

    DrawText("TEST", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

}

Sandbox::~Sandbox()
{

}
