#include "jsonParser.hpp"
#include "../scenes/lesson/lesson.hpp"

JsonParser::JsonParser()
{
    counter = 0;
}

void JsonParser::parseLesson(Lesson& lesson) //returns the continue key
{
    createEntities(lesson.doc, lesson.registry);
    loadRessources(lesson.doc, lesson.cacheManager);
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

void JsonParser::loadRessources(rj::Document& doc, CacheManager& cacheManager) //load the ressources into the cache
{

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
