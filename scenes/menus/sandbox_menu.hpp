#pragma once
#include "../scene.hpp"

class Sandbox: public Scene {
    public:
        Sandbox();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~Sandbox();
    private:
};
