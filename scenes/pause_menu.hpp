#pragma once
#include "scene.hpp"

class PauseMenu: public Scene {
    public:
        PauseMenu(entt::DefaultRegistry& registry);
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~PauseMenu();
    private:
        entt::DefaultRegistry& registry;
};
