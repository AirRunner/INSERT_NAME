#include "lesson.hpp"
#include "../menus/pause_menu.hpp"


Lesson::Lesson(std::string path)
{
    cacheManager = new CacheManager;
    systems::loadJson(doc, path.c_str());
    parser.parseLesson(*this);
    font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    text = "";
    float width = 1280;
    float height = 720;
    float padding = 50;
    rect =
    {
        padding,
        height-(height)/3+padding,
        width-2*padding,
        height/3 - 2*padding
    };
}

Lesson::Lesson(std::string path, CacheManager* cacheManager): cacheManager(cacheManager)
{
    systems::loadJson(doc, path.c_str());
    parser.parseLesson(*this);
    font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    text = "";
    float width = 1280;
    float height = 720;
    float padding = 50;
    rect =
    {
        padding,
        height-(height)/3+padding,
        width-2*padding,
        height/3 - 2*padding
    };
}

Scene* Lesson::handleEvents(float deltaTime)
{
    if(WindowShouldClose())
    {
        delete this;
        return nullptr;
    }
    if(IsKeyPressed(KEY_F10))
    {
        ToggleFullscreen();
    }
    if(IsKeyPressed(KEY_ESCAPE))
    {
        return new PauseMenu(this, this->cacheManager);
    }

    if(nextEvent == Null)
    {
        parser.parseLesson(*this);
    }

    if(nextEvent == Continue)
    {
        if(IsKeyPressed(KEY_ENTER))
        {
            parser.parseLesson(*this);
        }
        else if(IsKeyPressed(KEY_SPACE))
        {
            parser.parseLesson(*this);
        }
        else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            parser.parseLesson(*this);
        }
    }

    return this;
}

Scene* Lesson::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    animManager.udpateAnims(deltaTime);
    return this;
}

void Lesson::render() const
{
    systems::drawEntities(registry);
    DrawRectangleRounded(rect, 0.5, 10, GRAY);
    DrawRectangleRoundedLines(rect, 0.5, 10, 5, DARKGRAY);
    Rectangle newRec = systems::createRectangleForPadding(rect, 10, 10, 10, 10);
    systems::drawTextRecPro(font, text.c_str(), newRec, 40, 0, true, WHITE, 0, 0, WHITE, WHITE, 0, 0);
}

Lesson::~Lesson()
{

}
