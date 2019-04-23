#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <raylib.h>
#include <raymath.h>
#include <entt.hpp>
#include <rapidjson.h>

#include "../components/components.hpp"

namespace systems
{
    void updatePos(entt::DefaultRegistry* registry, float deltaTime);
    void drawEntities(entt::DefaultRegistry* registry);
}
