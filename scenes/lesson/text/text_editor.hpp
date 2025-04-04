#pragma once
#include "../../scene.hpp"

class TextEditor: public Scene {
    public:
        TextEditor();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~TextEditor();
    private:
};
