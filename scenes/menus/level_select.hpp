#pragma once
#include "../scene.hpp"
#include "../lesson/lesson.hpp"

class LevelSelect: public Scene {
    public:
        LevelSelect();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~LevelSelect();
    private:
        void resetButtons();
    private:
        Font font;
        rj::Document doc;
        int levelSelect;
        Vector2 mousePos;
        bool mouseActive;
};
