#include "sandbox.hpp"


Sandbox::Sandbox(entt::DefaultRegistry& registry) : registry(registry)
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
        [](auto entity, auto& movement)
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
        {
            DrawTexture(sprite.texture, movement.position.x, movement.position.y);
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
