#pragma once
#include "../scene.hpp"

class Lesson: public Scene {
    public:
        Lesson(std::string path);
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~Lesson();
    private:
        Font font;
        std::string text;
        rj::Document doc;
};
