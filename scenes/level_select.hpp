#pragma once
#include "scene.hpp"

class LevelSelect: public Scene {
    public:
        LevelSelect(entt::DefaultRegistry& registry);
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~LevelSelect();
    private:
        entt::DefaultRegistry& registry;
        Font font;
        int levelSelect;
};
