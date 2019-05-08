#include "jsonParser.hpp"
#include "../scenes/lesson/lesson.hpp"

JsonParser::JsonParser()
{
    counter = 0;
}

void JsonParser::parseLesson(Lesson& lesson) //returns the continue key
{
    updateText(lesson.doc, lesson.text);
    loadResources(lesson.doc, lesson.cacheManager);
    createEntities(lesson.doc, lesson.registry, lesson.cacheManager);
    parseAnim(lesson.doc, lesson.registry, lesson.animManager);
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
        //else, it remains the same
    }
}

void JsonParser::loadResources(rj::Document& doc, CacheManager* cacheManager) //load the ressources into the cache
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
                    cacheManager->textures.load<textureLoader>(entt::HashedString{texture[i]["id"].GetString()}, texture[i]["path"].GetString());
                }
            }
            if(cache["animation"].IsArray())
            {
                const rj::Value& animation = cache["animation"];
                for(rj::SizeType i = 0; i < animation.Size(); ++i)
                {
                    cacheManager->animations.load<animationLoader>(entt::HashedString{animation[i]["id"].GetString()}, animation[i]["path"].GetString(), animation[i]["animTime"].GetFloat());
                }
            }
            if(cache["music"].IsArray())
            {
                const rj::Value& music = cache["music"];
                for(rj::SizeType i = 0; i < music.Size(); ++i)
                {
                    cacheManager->musics.load<musicLoader>(entt::HashedString{music[i]["id"].GetString()}, music[i]["path"].GetString());
                }
            }
            if(cache["soundFX"].IsArray())
            {
                const rj::Value& soundFX = cache["soundFX"];
                for(rj::SizeType i = 0; i < soundFX.Size(); ++i)
                {
                    cacheManager->audios.load<soundFXLoader>(entt::HashedString{soundFX[i]["id"].GetString()}, soundFX[i]["path"].GetString());
                }
            }
        }
    }
}

void JsonParser::createEntities(rj::Document& doc, entt::DefaultRegistry* registry, CacheManager* cacheManager) //creates the appropiate entities
{
    if(doc[counter].IsObject())
    {
        if(doc[counter]["entities"].IsArray())
        {
            const rj::Value& entities = doc[counter]["entities"];
            std::uint32_t entity;
            std::string component;
            for(rj::SizeType i = 0; i < entities.Size(); ++i)
            {
                entity = registry->create();
                std::cout << "creating entity" << std::endl;
                for(rj::SizeType j = 0; j < entities[i].Size(); ++j)
                {
                    component = entities[i][j]["component"].GetString();
                    if(component == "sprite")
                    {
                        registry->assign<sprite>(entity, cacheManager->textures.handle(entt::HashedString{entities[i][j]["id"].GetString()}), entities[i][j]["width"].GetFloat(), entities[i][j]["height"].GetFloat());
                    }
                    else if(component == "position")
                    {
                        registry->assign<position>(entity, entities[i][j]["x"].GetFloat(),entities[i][j]["y"].GetFloat());
                    }
                    else if(component == "velocity")
                    {
                        registry->assign<velocity>(entity, entities[i][j]["x"].GetFloat(),entities[i][j]["y"].GetFloat());
                    }
                    else if(component == "animation")
                    {
                        registry->assign<animation>(entity, cacheManager->animations.handle(entt::HashedString{entities[i][j]["id"].GetString()}));
                    }
                    else if(component == "tag")
                    {
                        std::string tag = entities[i][j]["tag"].GetString();
                        if(tag == "player")
                        {
                            registry->assign<player>(entity);
                        }
                        else if(tag == "guide")
                        {
                            registry->assign<guide>(entity);
                        }
                        else if(tag == "nemesis")
                        {
                            registry->assign<nemesis>(entity);
                        }
                    }
                }
            }
        }
    }
}

void JsonParser::parseAnim(rj::Document& doc, entt::DefaultRegistry* registry, AnimManager& animManager) //parses and stores the animations in the lesson
{
    if(doc[counter].IsObject())
    {
        if(doc[counter]["animations"].IsArray())
        {
            const rj::Value& animations = doc[counter]["animations"];
            for(rj::SizeType i = 0; i < animations.Size(); ++i)
            {
                std::vector<AnimInfo> animInfos;
                std::uint32_t entity;
                std::string tag;
                std::string component;
                std::string attribute;
                for(rj::SizeType j = 0; j < animations[i].Size(); ++j)
                {
                    tag = animations[i][j]["tag"].GetString();
                    if(tag == "player")
                    {
                        const auto& view = registry->view<player>();
                        entity = view[0];
                    }
                    else if(tag == "guide")
                    {
                        const auto& view = registry->view<guide>();
                        entity = view[0];
                    }
                    else if(tag == "nemesis")
                    {
                        const auto& view = registry->view<nemesis>();
                        entity = view[0];
                    }
                    component = animations[i][j]["component"].GetString();
                    attribute = animations[i][j]["attribute"].GetString();
                    if(component == "position")
                    {
                        auto& pos = registry->get<position>(entity);
                        if(attribute == "x")
                        {
                            AnimInfo animInfo(animations[i][j]["type"].GetString(),
                                    animations[i][j]["option"].GetString(),
                                    pos.x,
                                    animations[i][j]["start"].GetFloat(),
                                    animations[i][j]["end"].GetFloat(),
                                    animations[i][j]["duration"].GetFloat());
                            animInfos.push_back(animInfo);
                        }
                        else if(attribute == "y")
                        {
                            AnimInfo animInfo(animations[i][j]["type"].GetString(),
                                    animations[i][j]["option"].GetString(),
                                    pos.y,
                                    animations[i][j]["start"].GetFloat(),
                                    animations[i][j]["end"].GetFloat(),
                                    animations[i][j]["duration"].GetFloat());
                            animInfos.push_back(animInfo);
                        }
                    }
                    else if(component == "velocity")
                    {
                        auto& vel = registry->get<velocity>(entity);
                        if(attribute == "x")
                        {
                            AnimInfo animInfo(animations[i][j]["type"].GetString(),
                                    animations[i][j]["option"].GetString(),
                                    vel.x,
                                    animations[i][j]["start"].GetFloat(),
                                    animations[i][j]["end"].GetFloat(),
                                    animations[i][j]["duration"].GetFloat());
                            animInfos.push_back(animInfo);
                        }
                        else if(attribute == "y")
                        {
                            AnimInfo animInfo(animations[i][j]["type"].GetString(),
                                    animations[i][j]["option"].GetString(),
                                    vel.y,
                                    animations[i][j]["start"].GetFloat(),
                                    animations[i][j]["end"].GetFloat(),
                                    animations[i][j]["duration"].GetFloat());
                            animInfos.push_back(animInfo);
                        }
                    }
                }
                animManager.animInfos.push_back(animInfos);
            }
        }
    }
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
