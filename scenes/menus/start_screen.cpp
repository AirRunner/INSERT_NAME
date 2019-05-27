#include "start_screen.hpp"
#include "level_select.hpp"
#include "../transition.hpp"

class LevelSelect;

StartScreen::StartScreen()
{
	cacheManager = new CacheManager;
    cacheManager->animations.load<animationLoader>(entt::HashedString{"credits"}, "data/assets/intro", 3000);

    std::uint32_t entity = registry->create();
    registry->assign<position>(entity, (float) screenWidth/2, (float) screenHeight/2);
    registry->assign<anim>(entity, cacheManager->animations.handle(entt::HashedString{"credits"}), 0.f, (float) screenWidth, (float) screenHeight);

    nextScene = new LevelSelect();
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

    if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_RIGHT)){
        return new Transition(this, nextScene, "left-right", "sine", "out", 800);
    }
    
    return this;
}

Scene* StartScreen::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    systems::updateAnims(registry, 2, deltaTime);
    return this;
}

void StartScreen::render() const
{
    systems::drawEntities(registry);
}

StartScreen::~StartScreen()
{

}
