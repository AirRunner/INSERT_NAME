#include "main_menu.hpp"


MainMenu::MainMenu()
{

}

Scene* MainMenu::handleEvents(float deltaTime)
{

    return this;
}

Scene* MainMenu::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    return this;
}

void MainMenu::render() const
{
    BeginDrawing();

    systems::drawEntities(registry);

    EndDrawing();
}

MainMenu::~MainMenu()
{

}
