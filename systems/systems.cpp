#include "systems.hpp"

void systems::updatePos(entt::DefaultRegistry* registry, float deltaTime)
{
    registry->view<movement>().each
    (
        [deltaTime](auto entity, auto& movement)
        {
            movement.position.x += movement.velocity.x * deltaTime;
            movement.position.y += movement.velocity.y * deltaTime;
        }
    );
}

void systems::drawEntities(entt::DefaultRegistry* registry)
{
    registry->view<sprite, movement>().each(
        [](auto entity, auto& sprite, auto& movement)
        {
            DrawTexture(sprite.texture, movement.position.x, movement.position.y, WHITE);
        }
    );
}
