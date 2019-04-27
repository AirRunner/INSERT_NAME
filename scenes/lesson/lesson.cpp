#include "lesson.hpp"


Lesson::Lesson(std::string path)
{
    systems::loadJson(doc, path.c_str());
    nextEvent = parser.parseLesson();
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

    if(nextEvent == Null)
    {
        nextEvent = parser.parseLesson();
    }

    if(nextEvent == Continue)
    {
        if(IsKeyPressed(KEY_ENTER))
        {
            nextEvent = parser.parseLesson();
        }
        else if(IsKeyPressed(KEY_SPACE))
        {
            nextEvent = parser.parseLesson();
        }
        else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            nextEvent = parser.parseLesson();
        }
    }

    return this;
}

Scene* Lesson::update(float deltaTime)
{
    systems::updatePos(registry, deltaTime);
    return this;
}

void Lesson::render() const
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawFPS(0,0);

    systems::drawEntities(registry);

    EndDrawing();
}

Lesson::~Lesson()
{

}
