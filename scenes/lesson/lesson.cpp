#include "lesson.hpp"


Lesson::Lesson(std::string path)
{
    std::ifstream ifs(path);
    rj::IStreamWrapper isw(ifs);
    doc.ParseStream(isw);
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

    systems::drawEntities(registry);

    ClearBackground(WHITE);

    DrawFPS(0,0);

    DrawText("TEST", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

}

Lesson::~Lesson()
{

}
