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

    EndDrawing();

}

Sandbox::~Sandbox()
{

}
