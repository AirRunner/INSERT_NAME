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

void Sandbox::render() const
{
    BeginDrawing();

    registry.view<sprite, movement>().each(
        [](auto entity, auto& sprite, auto& movement)
        {
            DrawTexture(sprite.texture, movement.position.x, movement.position.y, WHITE);
        }
    );

    ClearBackground(WHITE);

    DrawFPS(0,0);

    DrawText("TEST", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

}

Sandbox::~Sandbox()
{

}
