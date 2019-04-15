#pragma once
#include "scene.hpp"

class MainMenu: public Scene {
    public:
        MainMenu();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~MainMenu();
    private:
};
