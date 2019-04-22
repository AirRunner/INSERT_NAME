#include "pause_menu.hpp"


PauseMenu::PauseMenu()
{

}

Scene* PauseMenu::handleEvents(float deltaTime)
{

    return this;
}

Scene* PauseMenu::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    return this;
}

void PauseMenu::render() const
{
    BeginDrawing();

    systems::drawEntities(registry);

    EndDrawing();
}

PauseMenu::~PauseMenu()
{

}
