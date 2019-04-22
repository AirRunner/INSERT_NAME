#pragma once
#include "../../scene.hpp"

class VisualEditor: public Scene {
    public:
        VisualEditor();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~VisualEditor();
    private:
};
