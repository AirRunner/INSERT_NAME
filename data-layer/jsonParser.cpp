#include "jsonParser.hpp"


Event JsonParser::parseLesson() //returns the continue key
{
    createEntities();
    parseAnim();
    updateText();
    parseTransition();
    return parseEvent();
}

void JsonParser::updateText() //updates the text of the scene
{

}

void JsonParser::createEntities() //creates the appropiate entities
{

}

void JsonParser::parseAnim() //parses and executes the animations
{

}

void JsonParser::parseTransition() //parses and execute the transition between two screens
{

}

Event JsonParser::parseEvent() //parses and returns the continue key
{
    
    return Continue;
}
