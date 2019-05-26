#include "lesson.hpp"
#include "../menus/pause_menu.hpp"


Lesson::Lesson(std::string path)
{
    cacheManager = new CacheManager;
    systems::loadJson(doc, path.c_str());
    parser.parseLesson(*this);
    font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 60, NULL, 600);
    float width = screenWidth;
    float height = screenHeight;
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
    font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 60, NULL, 600);
    float width = screenWidth;
    float height = screenHeight;
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
    if(IsKeyPressed(KEY_F11))
    {
        systems::toggleFullscreen();
    }
    if(IsKeyPressed(KEY_ESCAPE))
    {
        return new PauseMenu(this, this->cacheManager);
    }

    if(nextEvent == Null)
    {
        return parser.parseLesson(*this);
    }
    else if(nextEvent == Continue)
    {
        if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_RIGHT))
        {
            if(!text.isUpdateComplete())
                text.completeText();
            else
                return parser.parseLesson(*this);
        }
    }

    return this;
}


Scene* Lesson::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    systems::updateAnims(registry, 3, deltaTime);
    systems::updateMusic(registry);
    animManager.udpateAnims(deltaTime);
    text.updateText(deltaTime);
    return this;
}

void Lesson::render() const
{
    systems::drawEntities(registry);
    DrawRectangleRounded(rect, 0.5, 10, GRAY);
    DrawRectangleRoundedLines(rect, 0.5, 10, 5, DARKGRAY);
    Rectangle newRec = systems::createRectangleForPadding(rect, 40, 40, 40, 40);
    systems::drawTextRecPro(font, text.ptext.c_str(), newRec, 60, 0, true, WHITE, 0, 0, WHITE, WHITE, 0, 0);
}

Lesson::~Lesson()
{

}
