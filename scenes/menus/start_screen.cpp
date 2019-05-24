#include "start_screen.hpp"


StartScreen::StartScreen()
{
	cacheManager = new CacheManager;

}

Scene* StartScreen::handleEvents(float deltaTime)
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

Scene* StartScreen::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    return this;
}

void StartScreen::render() const
{
    systems::drawEntities(registry);
}

StartScreen::~StartScreen()
{

}
