#pragma once
#include "../scene.hpp"

class Lesson: public Scene {
    public:
        Lesson();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~Lesson();
    private:
};
