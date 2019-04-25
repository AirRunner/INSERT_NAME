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

void systems::drawButtons(entt::DefaultRegistry* registry, const Font& font, float fontSize, float spacing)
{
    registry->view<button>().each(
        [font, fontSize, spacing](auto entity, auto& button)
        {
            Color color = GRAY;
            if(button.selected)
            {
                color = LIGHTGRAY;
            }
            DrawRectangleRounded(button.rect, 0.3, 10, color);
            DrawTextRec(font, button.text.c_str(), button.rect, fontSize, spacing, true, button.color);
        }
    );
}

int systems::updateButtons(entt::DefaultRegistry* registry, Vector2 mousePos, bool mouseActive, int selected)
{
    int id = selected;
    registry->view<button>().each(
        [mousePos, mouseActive, &id](auto entity, auto& button)
        {
            if((mouseActive && CheckCollisionPointRec(mousePos, button.rect)) || id == button.id)
            {
                button.selected = 1;
                id = button.id;
            }
            else if(id != button.id)
            {
                button.selected = 0;
            }
        }
    );
    return id;
}
