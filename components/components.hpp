#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP value

#include <entt.hpp>
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

struct button
{
    Rectangle rect;
    std::string text;
    Color color;
    bool selected;
    int id;
};

#endif /* ifndef COMPONENTS_HPP */
