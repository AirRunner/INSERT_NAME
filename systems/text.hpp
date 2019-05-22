#pragma once

#include <iostream>
#include <raylib.h>
#include "easings.h"
#include <list>

class Text
{
    public:
        Text();
        ~Text() = default;
        void addText(std::string value, float interval);
        void updateText(float deltaTime);
        bool isUpdateComplete();
        void completeText();
        void reservePrintText();
        friend class Lesson;
        friend class JsonParser;
    private :
        std::list<std::pair<std::string, float>> text;
        std::pair<std::string, float> currentText;
        std::string ptext;
        float currentTime;
        int currentIndice;
        int maximumSize;
};
