#pragma once

#include <iostream>
#include <vector>
#include "easings.h"

class AnimInfo;

class AnimManager
{
    public:
        AnimManager() = default;
        ~AnimManager() = default;
        friend class JsonParser;
        void udpateAnims();
    private:
        std::vector<std::vector<AnimInfo>> AnimInfos;
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
