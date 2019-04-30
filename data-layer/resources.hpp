#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

#include <raylib.h>
#include <raymath.h>

#include <entt.hpp>

//The different resources
struct texture
{
        texture(const char* path);
        ~texture();

        Texture2D tex;
};

struct animation
{
        animation(int size, float animTime, Texture2D* anim);
        ~animation();

        int size;
        float animTime;
        Texture2D* anim;
};

struct music
{
        music(const char* path);
        ~music();

        Music audio;
};

struct soundFX
{
        soundFX(const char* path);
        ~soundFX();

        Sound audio;
};

//The loader for the resources must be structs to expose load function
struct textureLoader final: entt::ResourceLoader<textureLoader, texture>
{
    std::shared_ptr<texture> load(const char* path) const;
};

struct animationLoader final: entt::ResourceLoader<animationLoader, animation>
{
    std::shared_ptr<animation> load(const std::string path, float animTime) const;
};

struct musicLoader final: entt::ResourceLoader<musicLoader, music>
{
    std::shared_ptr<music> load(const char* path) const;
};

struct soundFXLoader final: entt::ResourceLoader<soundFXLoader, soundFX>
{
    std::shared_ptr<soundFX> load(const char* path) const;
};
