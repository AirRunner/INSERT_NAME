#include "sandbox_menu.hpp"


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
    systems::updatePos(registry, deltaTime);
    return this;
}

void Sandbox::render() const
{
    systems::drawEntities(registry);

    DrawText("TEST", 190, 200, 20, LIGHTGRAY);
}

Sandbox::~Sandbox()
{

}
