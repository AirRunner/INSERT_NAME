#pragma once
#include "../../scene.hpp"

class TextRep: public Scene {
    public:
        TextRep();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~TextRep();
    private:
};
