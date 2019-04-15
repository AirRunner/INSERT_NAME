#pragma once
#include "scene.hpp"

class PauseMenu: public Scene {
    public:
        PauseMenu();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~PauseMenu();
    private:
};
