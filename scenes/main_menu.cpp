#include "main_menu.hpp"


MainMenu::MainMenu(entt::DefaultRegistry& registry) : registry(registry)
{

}

Scene* MainMenu::handleEvents(float deltaTime)
{

    return this;
}

Scene* MainMenu::update(float deltaTime)
{
    registry.view<movement>().each
    (
        [](auto entity, auto& movement)
        {
            movement.position.x += movement.velocity.x * deltaTime;
            movement.position.y += movement.velocity.y * deltaTime;
        }
    );
    return this;
}

void MainMenu::render() const
{
    BeginDrawing();

    registry.view<sprite, movement>().each(
        {
            DrawTexture(sprite.texture, movement.position.x, movement.position.y);
        }
    );

    EndDrawing();
}

MainMenu::~MainMenu()
{

}
