#pragma once

#include <iostream>
#include <vector>
#include "easings.h"
#include <raylib.h>

class AnimInfo;

class AnimManager
{
    public:
        AnimManager();
        ~AnimManager() = default;
        friend class JsonParser;
        void udpateAnims(float deltaTime);
    private:
        int counter;
        std::vector<std::vector<AnimInfo>> animInfos;
};

class AnimInfo
{
    public:
        AnimInfo(std::string animType, std::string animOption, float& param, float paramStart, float paramStop, float animTime);
        ~AnimInfo() = default;
        friend class AnimManager;
    private:
        float (*animFunc)(float currentTime, float paramStart, float paramChange, float animTime);
        float& param;
        float currentTime;
        float paramStart;
        float paramChange;
        float animTime;
};
