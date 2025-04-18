#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP value

#include <entt.hpp>
#include <raylib.h>
#include "resources.hpp"

struct sprite
{
    entt::ResourceHandle<texture> texHandle;
    float width;
    float height;
};

struct anim
{
    entt::ResourceHandle<animation> animHandle;
    float index;
    float width;
    float height;
};

struct position
{
    float x;
    float y;
};

struct velocity
{
    float x;
    float y;
};

struct button
{
    entt::ResourceHandle<texture> texHandle;
    entt::ResourceHandle<animation> animHandle;
    Rectangle rect;
    float index;
    std::string text;
    Color color;
    Texture2D* tex;
    bool selected;
    int id;
};

struct bMusic
{
    entt::ResourceHandle<music> musicHandle;
};

struct tool
{
    entt::ResourceHandle<texture> texHandle;
    float width;
    float height;
};

struct player
{

};
struct guide
{

};
struct nemesis
{

};

#endif /* ifndef COMPONENTS_HPP */
