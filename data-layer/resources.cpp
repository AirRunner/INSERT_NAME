#include "resources.hpp"

//constructor and destructor of resources
texture::texture(const char* path)
{
    tex = LoadTexture(path);
}

texture::~texture()
{
    UnloadTexture(tex);
}

animation::animation(int size, float animTime, Texture2D* anim): size(size), animTime(animTime), anim(anim)
{

}

animation::~animation()
{
    for(int i = 0; i < size; ++i)
    {
        UnloadTexture(anim[i]);
    }
    free(anim);
}

music::music(const char* path)
{
    audio = LoadMusicStream(path);
}

music::~music()
{
    UnloadMusicStream(audio);
}

soundFX::soundFX(const char* path)
{
    audio = LoadSound(path);
}

soundFX::~soundFX()
{
    UnloadSound(audio);
}

//loaders
std::shared_ptr<texture> textureLoader::load(const char* path) const
{
    return std::shared_ptr<texture>(new texture{path});
}

std::shared_ptr<animation> animationLoader::load(const std::string path, float animTime) const
{
    std::vector<std::string> paths;

    for(const fs::directory_entry& entry : fs::directory_iterator(path))
    {
        paths.push_back(entry.path().string());
    }

    std::sort(paths.begin(), paths.end());

    Texture2D* anim = new Texture2D[paths.size()];

    for(int i = 0; i < (int) paths.size(); ++i)
    {
        anim[i] = LoadTexture(paths[i].c_str());
    }

    return std::shared_ptr<animation>(new animation{(int) paths.size(), animTime, anim});
}

std::shared_ptr<music> musicLoader::load(const char* path) const
{
    return std::shared_ptr<music>(new music{path});
}

std::shared_ptr<soundFX> soundFXLoader::load(const char* path) const
{
    return std::shared_ptr<soundFX>(new soundFX{path});
}
