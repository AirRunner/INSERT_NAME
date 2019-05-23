#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>

#include <raylib.h>
#include <raymath.h>

#include <entt.hpp>

#include <document.h>
#include <istreamwrapper.h>
namespace rj = rapidjson;

#include "../components/components.hpp"


namespace systems
{
    void updatePos(entt::DefaultRegistry* registry, float deltaTime);
    void drawEntities(entt::DefaultRegistry* registry);
    void drawButtons(entt::DefaultRegistry* registry, const Font& font, float fontSize, float spacing);
    int updateButtons(entt::DefaultRegistry* registry, Vector2 mousePos, bool mouseActive, int selected);
    bool checkCollisionMouseButtons(entt::DefaultRegistry* registry, Vector2 mousePos);
    bool checkCollisionMouseSprite(entt::DefaultRegistry* registry, Vector2 mousePos);
    void loadJson(rj::Document& doc, const char* path);
    void drawTextRecPro(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectText, Color selectBack, int halign, int valign);
    int MeasureHeightTextRec(Font font, const char *text, Rectangle rec, float fontSize, float spacing);
    Rectangle createRectangleForPadding(Rectangle rec, float top, float left, float right, float bottom);
}
