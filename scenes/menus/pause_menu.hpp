#pragma once
#include "../scene.hpp"
#include "../../data-layer/cacheManager.hpp"

class PauseMenu: public Scene {
    public:
        PauseMenu(Scene* resumeScene);
        PauseMenu(Scene* resumeScene, CacheManager* cacheManager);
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~PauseMenu();
    private:
        void initButtons();

        Scene* resumeScene;

        entt::DefaultRegistry* registry;
        CacheManager* cacheManager;

        Font font;
        Camera2D camera;
        int selected;
        int size;
        Vector2 mousePos;
        bool mouseActive;
};
