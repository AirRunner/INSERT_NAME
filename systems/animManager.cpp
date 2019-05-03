#include "animManager.hpp"


void AnimManager::udpateAnims()
{

}


AnimInfo::AnimInfo(std::string animType, std::string animOption, float& param, float paramStart, float paramStop, float animTime): param(param), paramStart(paramStart), paramChange(paramStop-paramStart), animTime(animTime)
{
    if(animType == "linear")
    {
        animFunc = EaseLinearNone;
    }
    if(animType == "sine")
    {
        if(animOption == "in")
        {
            animFunc = EaseSineIn;
        }
        if(animOption == "out")
        {
            animFunc = EaseSineOut;
        }
        if(animOption == "in-out")
        {
            animFunc = EaseSineInOut;
        }
    }
    if(animType == "circ")
    {
        if(animOption == "in")
        {
            animFunc = EaseCircIn;
        }
        if(animOption == "out")
        {
            animFunc = EaseCircOut;
        }
        if(animOption == "in-out")
        {
            animFunc = EaseCircInOut;
        }
    }
    if(animType == "cubic")
    {
        if(animOption == "in")
        {
            animFunc = EaseCubicIn;
        }
        if(animOption == "out")
        {
            animFunc = EaseCubicOut;
        }
        if(animOption == "in-out")
        {
            animFunc = EaseCubicInOut;
        }
    }
    if(animType == "quad")
    {
        if(animOption == "in")
        {
            animFunc = EaseQuadIn;
        }
        if(animOption == "out")
        {
            animFunc = EaseQuadOut;
        }
        if(animOption == "in-out")
        {
            animFunc = EaseQuadInOut;
        }
    }
    if(animType == "expo")
    {
        if(animOption == "in")
        {
            animFunc = EaseExpoIn;
        }
        if(animOption == "out")
        {
            animFunc = EaseExpoOut;
        }
        if(animOption == "in-out")
        {
            animFunc = EaseExpoInOut;
        }
    }
    if(animType == "back")
    {
        if(animOption == "in")
        {
            animFunc = EaseBackIn;
        }
        if(animOption == "out")
        {
            animFunc = EaseBackOut;
        }
        if(animOption == "in-out")
        {
            animFunc = EaseBackInOut;
        }
    }
    if(animType == "bounce")
    {
        if(animOption == "in")
        {
            animFunc = EaseBounceIn;
        }
        if(animOption == "out")
        {
            animFunc = EaseBounceOut;
        }
        if(animOption == "in-out")
        {
            animFunc = EaseBounceInOut;
        }
    }
    if(animType == "elastic")
    {
        if(animOption == "in")
        {
            animFunc = EaseElasticIn;
        }
        if(animOption == "out")
        {
            animFunc = EaseElasticOut;
        }
        if(animOption == "in-out")
        {
            animFunc = EaseElasticInOut;
        }
    }
}
