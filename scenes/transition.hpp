#pragma once
#include "scene.hpp"
#include "../systems/animManager.hpp"

class Transition : public Scene
{
    public:
        Transition(Scene* previous, Scene* next, std::string direction, std::string animType, std::string animOption, float animTime);
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~Transition();
    private:
        Scene* previous;
        Scene* next;

        AnimInfo* animPrev;
        AnimInfo* animNext;

        Camera2D camPrev;
        Camera2D camNext;
};
