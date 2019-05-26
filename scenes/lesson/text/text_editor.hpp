#pragma once
#include "../../scene.hpp"
#include <cling/Interpreter/Interpreter.h>
#include <cling/Interpreter/Value.h>
#include <cling/Utils/Casting.h>

// namespace ci = cling::Interpreter;

class TextEditor: public Scene {
    public:
        TextEditor();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~TextEditor();
    private:
    	Font font;
    	Rectangle rect;
    	int file;
    	char** droppedFiles;
    	// cling::Interpreter* interp;
};
