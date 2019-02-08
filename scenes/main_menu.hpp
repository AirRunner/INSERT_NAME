#pragma once
#include "scene.hpp"

class MainMenu: public Scene {
    public:
        MainMenu(entt::DefaultRegistry& registry);
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~MainMenu();
    private:
        entt::DefaultRegistry& registry;
};
