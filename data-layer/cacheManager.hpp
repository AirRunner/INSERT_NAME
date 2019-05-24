#pragma once

#include "resources.hpp"

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
        friend class VisualEditor;

    private:
        //The resource caches
        textureCache textures;
        animationCache animations;
        musicCache musics;
        soundFXCache audios;
};
