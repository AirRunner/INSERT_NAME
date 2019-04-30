#include "jsonParser.hpp"
#include "../scenes/lesson/lesson.hpp"

JsonParser::JsonParser()
{
    counter = 0;
}

void JsonParser::parseLesson(Lesson& lesson) //returns the continue key
{
    createEntities(lesson.doc, lesson.registry);
    loadResources(lesson.doc, lesson.cacheManager);
    parseAnim(lesson.doc, lesson.registry);
    updateText(lesson.doc, lesson.text);
    parseTransition(lesson);
    parseEvent(lesson.doc, lesson.nextEvent);
}

void JsonParser::updateText(rj::Document& doc, std::string& text) //updates the text of the scene
{
    if(doc[counter].IsObject())
    {
        if(doc[counter]["text"].IsString())
        {
            text = doc[counter]["text"].GetString();
        }
        else
        {
            text = "";
        }
    }
}

void JsonParser::loadResources(rj::Document& doc, CacheManager& cacheManager) //load the ressources into the cache
{
    if(doc[counter].IsObject())
    {
        if(doc[counter]["cache"].IsObject())
        {
            const rj::Value& cache = doc[counter]["cache"];
            if(cache["texture"].IsArray())
            {
                const rj::Value& texture = cache["texture"];
                for(rj::SizeType i = 0; i < texture.Size(); ++i)
                {
                    cacheManager.textures.load<textureLoader>(entt::HashedString{texture[i]["id"].GetString()}, texture[i]["path"].GetString());
                }
            }
            if(cache["animation"].IsArray())
            {
                const rj::Value& animation = cache["animation"];
                for(rj::SizeType i = 0; i < animation.Size(); ++i)
                {
                    cacheManager.animations.load<animationLoader>(entt::HashedString{animation[i]["id"].GetString()}, animation[i]["path"].GetString(), animation[i]["animTime"].GetFloat());
                }
            }
            if(cache["music"].IsArray())
            {
                const rj::Value& music = cache["music"];
                for(rj::SizeType i = 0; i < music.Size(); ++i)
                {
                    cacheManager.musics.load<musicLoader>(entt::HashedString{music[i]["id"].GetString()}, music[i]["path"].GetString());
                }
            }
            if(cache["soundFX"].IsArray())
            {
                const rj::Value& soundFX = cache["soundFX"];
                for(rj::SizeType i = 0; i < soundFX.Size(); ++i)
                {
                    cacheManager.audios.load<soundFXLoader>(entt::HashedString{soundFX[i]["id"].GetString()}, soundFX[i]["path"].GetString());
                }
            }
        }
    }
}

void JsonParser::createEntities(rj::Document& doc, entt::DefaultRegistry* registry) //creates the appropiate entities
{

}

void JsonParser::parseAnim(rj::Document& doc, entt::DefaultRegistry* registry) //parses and executes the animations
{

}

void JsonParser::parseTransition(Lesson& lesson) //parses and execute the transition between two screens
{

}

void JsonParser::parseEvent(rj::Document& doc, Event& nextEvent) //parses and returns the continue key
{
    if(doc[counter].IsObject())
    {
        if(doc[counter]["event"].IsString())
        {
            std::string event = doc[counter]["event"].GetString();

            if(event == "continue")
            {
                nextEvent = Continue;
            }
            if(event == "block")
            {
                nextEvent = Block;
            }
        }
        else
        {
            nextEvent = Null;
        }
        counter++;
    }
}
