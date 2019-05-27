#pragma once

#include <fstream>
#include <document.h>
#include <istreamwrapper.h>
namespace rj = rapidjson;

#include "cacheManager.hpp"
#include "../systems/animManager.hpp"
#include "../systems/text.hpp"
#include "../components/components.hpp"


typedef enum
{
    Continue,
    Null,
    Block
} Event;

class Lesson;
class Scene;
class VisualEditor;

class JsonParser
{
    public:
        JsonParser();
        Scene* parseLesson(Lesson& lesson); //returns the transition scene if one is created
        Scene* parseVisual(VisualEditor& visualEditor);

    private:
        int counter;

        //helper functions for parseLesson()

        void updateText(rj::Document& doc, Text& text); //updates the text of the scene
        void loadResources(rj::Document& doc, CacheManager* cacheManager); //load the ressources into the cache
        void createEntities(rj::Document& doc, entt::DefaultRegistry* registry, CacheManager* cacheManager); //creates the appropiate entities
        void parseAnim(rj::Document& doc, entt::DefaultRegistry* registry, AnimManager& animManager); //parses and executes the animations
        void parseEvent(rj::Document& doc, Event& nextEvent); //parses and changes the nextEvent param
        Scene* parseTransition(Lesson& lesson); //parses and creates transition screen if one is called

        //helper functions for parseAnim()


};
