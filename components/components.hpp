#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP value

#include <entt.hpp>
#include <raylib.h>
#include "resources.hpp"

struct sprite
{
    entt::ResourceHandle<texture> tex;
};

struct anim
{
    entt::ResourceHandle<animation> anim;
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
    Rectangle rect;
    std::string text;
    Color color;
    bool selected;
    int id;
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
