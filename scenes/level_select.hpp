#pragma once
#include "scene.hpp"

class LevelSelect: public Scene {
    public:
        LevelSelect();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~LevelSelect();
    private:
        Font font;
        int levelSelect;
};
