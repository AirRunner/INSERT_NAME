#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP value

#include <entt/entt.hpp>
#include <raylib.h>

struct sprite
{
    Texture2D texture;
};

struct movement
{
    Vector2 position;
    Vector2 velocity;
};

#endif /* ifndef COMPONENTS_HPP */
