#include "transition.hpp"

Transition::Transition(Scene* previous, Scene* next, std::string direction, std::string animType, std::string animOption, float animTime): previous(previous), next(next)
{
    camPrev.target = {(float) GetScreenWidth()/2,(float) GetScreenHeight()/2};
    camPrev.offset = {0,0};
    camPrev.rotation = 0.f;
    camPrev.zoom = 1.f;

    camNext = camPrev;

    if(direction == "left-right")
    {
        animPrev = new AnimInfo(animType, animOption, camPrev.offset.x, 0, -GetScreenWidth(), animTime);
        animNext = new AnimInfo(animType, animOption, camNext.offset.x, GetScreenWidth(), 0, animTime);
        camNext.offset.x -= GetScreenWidth();
    }
    else if(direction == "right-left")
    {
        animPrev = new AnimInfo(animType, animOption, camPrev.offset.x, 0, GetScreenWidth(), animTime);
        animNext = new AnimInfo(animType, animOption, camNext.offset.x, -GetScreenWidth(), 0, animTime);
        camNext.offset.x += GetScreenWidth();
    }
    else if(direction == "bottom-up")
    {
        animPrev = new AnimInfo(animType, animOption, camPrev.offset.y, 0, GetScreenWidth(), animTime);
        animNext = new AnimInfo(animType, animOption, camNext.offset.y, -GetScreenWidth(), 0, animTime);
        camNext.offset.y += GetScreenHeight();
    }
    else if(direction == "top-down")
    {
        animPrev = new AnimInfo(animType, animOption, camPrev.offset.y, 0, -GetScreenWidth(), animTime);
        animNext = new AnimInfo(animType, animOption, camNext.offset.y, GetScreenWidth(), 0, animTime);
        camNext.offset.y -= GetScreenHeight();
    }
    else
    {
        TraceLog(LOG_INFO, "Failed initialization of transition animInfo: Verify your json file");
        animNext = animPrev = nullptr;
    }
}
Scene* Transition::handleEvents(float deltaTime)
{
    return this;
}
Scene* Transition::update(float deltaTime)
{
    bool updated = false;
    if(animPrev->currentTime < animPrev->animTime)
    {
        animPrev->currentTime += deltaTime;
        if(animPrev->currentTime > animPrev->animTime)
        {
            animPrev->currentTime = animPrev->animTime;
        }
        animPrev->param = animPrev->animFunc(animPrev->currentTime, animPrev->paramStart, animPrev->paramChange, animPrev->animTime);
        TraceLog(LOG_INFO, "param Prev: %f", animPrev->param);
        updated = true;
    }
    if(animNext->currentTime < animNext->animTime)
    {
        animNext->currentTime += deltaTime;
        if(animNext->currentTime > animNext->animTime)
        {
            animNext->currentTime = animNext->animTime;
        }
        animNext->param = animNext->animFunc(animNext->currentTime, animNext->paramStart, animNext->paramChange, animNext->animTime);
        TraceLog(LOG_INFO, "param Next: %f", animNext->param);
        updated = true;
    }
    
    if(!updated)
    {
        delete previous;
        Scene* tmp = next;
        delete this;
        return tmp;
    }
    return this;
}
void Transition::render() const
{
    systems::drawEntities(registry);

    BeginMode2D(camPrev);
        previous->render();
    EndMode2D();
    BeginMode2D(camNext);
        next->render();
    EndMode2D();
}
Transition::~Transition()
{

}
