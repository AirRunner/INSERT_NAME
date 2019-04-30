#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <map>
#include <filesystem>

#include <raylib.h>
#include <raymath.h>

#include <entt.hpp>

#include <document.h>
#include <istreamwrapper.h>
namespace rj = rapidjson;

#include "../components/components.hpp"

namespace fs = std::filesystem;

//The different resources
class texture
{
    public:
        texture(const char* path);
        ~texture();

    private:
        Texture2D tex;
};

class animation
{
    public:
        animation(int size, float animTime, Texture2D* anim);
        ~animation();

    private:
        int size;
        float animTime;
        Texture2D* anim;
};

class music
{
    public:
        music(const char* path);
        ~music();

    private:
        Music audio;
};

class soundFX
{
    public:
        soundFX(const char* path);
        ~soundFX();

    private:
        Sound audio;
};

//The loader for the resources
class textureLoader final: entt::ResourceLoader<textureLoader, texture>
{
    std::shared_ptr<texture> load(const char* path) const;
};

class animationLoader final: entt::ResourceLoader<animationLoader, animation>
{
    std::shared_ptr<animation> load(const std::string path, float animTime) const;
};

class musicLoader final: entt::ResourceLoader<musicLoader, music>
{
    std::shared_ptr<music> load(const char* path) const;
};

class soundFXLoader final: entt::ResourceLoader<soundFXLoader, soundFX>
{
    std::shared_ptr<soundFX> load(const char* path) const;
};

//The cache type shortcuts
using textureCache = entt::ResourceCache<texture>;
using animationCache = entt::ResourceCache<animation>;
using musicCache = entt::ResourceCache<music>;
using soundFXCache = entt::ResourceCache<soundFX>;

//The CacheManger class
class CacheManager
{
    public:
        friend class JsonParser;

    private:
        //The resource caches
        textureCache textures;
        animationCache animations;
        musicCache musics;
        soundFXCache audios;
};
