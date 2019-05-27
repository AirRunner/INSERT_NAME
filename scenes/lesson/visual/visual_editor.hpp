#pragma once
#include "../../scene.hpp"
#include "../../data-layer/jsonParser.hpp"
//#include "../../systems/animManager.hpp"

class VisualEditor: public Scene {
    public:
        VisualEditor();
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~VisualEditor();
        
        friend class JsonParser;
        
    private:
        rj::Document doc;
        JsonParser parser;
        CacheManager* cacheManager;
        //AnimManager animManager;
        uint32_t selectedSprite = -1;
        uint32_t selectedTool = -1;
        Vector2 mousePos;
};
