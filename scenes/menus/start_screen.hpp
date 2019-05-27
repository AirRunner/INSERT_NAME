#pragma once
#include "../scene.hpp"
#include "../../data-layer/cacheManager.hpp"

class StartScreen: public Scene {
    public:
        StartScreen();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~StartScreen();
    private:
    	CacheManager* cacheManager;
    	Scene* nextScene;
};
