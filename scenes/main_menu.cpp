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
    registry.view<movement>().each
    (
        [deltaTime](auto entity, auto& movement)
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
        [](auto entity, auto& sprite, auto& movement)
        {
            DrawTexture(sprite.texture, movement.position.x, movement.position.y, WHITE);
        }
    );

    EndDrawing();
}

MainMenu::~MainMenu()
{

}
