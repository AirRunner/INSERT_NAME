#include "lesson.hpp"
#include "../menus/pause_menu.hpp"
#include "../../data-layer/cacheManager.hpp"


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
    
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        registry->view<position, velocity>().each(
            [mousePos](auto entity, auto& position, auto& velocity)
            {
                position.x = mousePos.x;
                position.y = mousePos.y;
            }
        );
    }

    if(nextEvent == Null)
    {
        return parser.parseLesson(*this);
    }
    else if(nextEvent == Continue)
    {
        if(IsKeyPressed(KEY_ENTER) ||
            IsKeyPressed(KEY_SPACE) ||
            IsKeyPressed(KEY_RIGHT) ||
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
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
    text.updateText(deltaTime, cacheManager->audios.handle(entt::HashedString{"text"})->audio);
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
