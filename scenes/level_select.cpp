#include "level_select.hpp"


LevelSelect::LevelSelect(entt::DefaultRegistry& registry) : registry(registry)
{
    font = LoadFontEx("../data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    levelSelect = 0;
}

Scene* LevelSelect::handleEvents(float deltaTime)
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

Scene* LevelSelect::update(float deltaTime)
{

    return this;
}

void LevelSelect::render() const
{
    float fontSize = 40;
    float spacing = 0;
    char numLevel[4];
    sprintf(numLevel, "%d", levelSelect);
    BeginDrawing();

    ClearBackground(BLACK);

    DrawTextEx(font, "1 \n2 \n3 \n4 \n5 \n6 ", {0,0}, fontSize, spacing, DARKGRAY);
    DrawTextEx(font, "vector<int>            ;\n\n\nint newLevel = access(                 );", {fontSize, 0}, fontSize, spacing, GRAY);
    DrawTextEx(font, "levelSelect", Vector2Add(MeasureTextEx(font, "vector<int> ", fontSize, spacing), {fontSize, -fontSize}), fontSize, spacing, WHITE); //has to be a ttf cause here it's not and it's an absolute mess...
    DrawTextEx(font, "levelSelect[   ]", Vector2Add(MeasureTextEx(font, "\n\n\nint newLevel = access( ", fontSize, spacing), {fontSize, -fontSize}), fontSize, spacing, WHITE); //has to be a ttf cause here it's not and it's an absolute mess...
    DrawTextEx(font, numLevel, Vector2Add(MeasureTextEx(font, "\n\n\nint newLevel = access( levelSelect[ ", fontSize, spacing), {fontSize, -fontSize}), fontSize, spacing, WHITE); //has to be a ttf cause here it's not and it's an absolute mess...

    EndDrawing();
}

LevelSelect::~LevelSelect()
{
    UnloadFont(font);
}
