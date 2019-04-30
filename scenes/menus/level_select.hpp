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
        void resetButtons(bool level);

        Font font;
        rj::Document doc;
        rj::SizeType size;
        int levelSelect;
        Camera2D camera;
        Vector2 mousePos;
        bool mouseActive;
};
