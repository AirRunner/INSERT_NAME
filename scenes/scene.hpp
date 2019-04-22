#pragma once
#include "../systems/systems.hpp"
#include "../components/components.hpp"

class Scene {
    public:
        Scene();
        virtual Scene* handleEvents(float deltaTime) = 0; //using pure virtual functions to force implementation by sub-classes
        virtual Scene* update(float deltaTime) = 0;
        virtual void render() const = 0;
        virtual ~Scene();

    protected:
        entt::DefaultRegistry* registry;
};
