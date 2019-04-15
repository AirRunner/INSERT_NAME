#include "scene.hpp"


Scene::Scene()
{
    registry = new entt::DefaultRegistry{};
}

Scene::~Scene()
{
    delete &registry;
}
