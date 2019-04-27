#pragma once

#include <iostream>
#include <rapidjson.h>
#include <raylib.h>

typedef enum
{
    Continue,
    Null
} Event;

class JsonParser
{
    public:
        Event parseLesson(); //returns the continue key

    private:
        int counter;

        //helper functions for parseLesson()

        void updateText(); //updates the text of the scene
        void createEntities(); //creates the appropiate entities
        void parseAnim(); //parses and executes the animations
        void parseTransition(); //parses and execute the transition between two screens
        Event parseEvent(); //parses and returns the continue key

        //helper functions for parseAnim()


};
