#pragma once
#include "../../scene.hpp"

class VisualRep: public Scene {
    public:
        VisualRep();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~VisualRep();
    private:
};
