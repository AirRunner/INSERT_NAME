#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <map>

#include <raylib.h>
#include <raymath.h>

#include <entt.hpp>

#include <document.h>
#include <istreamwrapper.h>
namespace rj = rapidjson;

#include "../components/components.hpp"

typedef enum
{
    Continue,
    Null,
    Block
} Event;

class Lesson;

class JsonParser
{
    public:
        JsonParser();
        void parseLesson(Lesson& lesson); //returns the continue key

    private:
        int counter;

        //helper functions for parseLesson()

        void updateText(rj::Document& doc, std::string& text); //updates the text of the scene
        void loadRessources(Lesson& lesson); //load the ressources into the cache
        void createEntities(rj::Document& doc, entt::DefaultRegistry* registry); //creates the appropiate entities
        void parseAnim(rj::Document& doc, entt::DefaultRegistry* registry); //parses and executes the animations
        void parseTransition(Lesson& lesson); //parses and execute the transition between two screens
        void parseEvent(rj::Document& doc, Event& nextEvent); //parses and returns the continue key

        //helper functions for parseAnim()


};
