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
        friend class StartScreen;
        friend class VisualEditor;
        friend class LevelSelect;
        friend class PauseMenu;
        musicCache musics;
        soundFXCache audios;

    private:
        //The resource caches
        textureCache textures;
        animationCache animations;
};
