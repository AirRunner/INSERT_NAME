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
    systems::drawEntities(registry);
}

MainMenu::~MainMenu()
{

}
