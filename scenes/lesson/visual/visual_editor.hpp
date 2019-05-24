#pragma once
#include "../../scene.hpp"
#include "../../data-layer/jsonParser.hpp"

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
        CacheManager* cacheManager;
        JsonParser parser;
        uint32_t selectedEntity = -1;
        Vector2 mousePos;
};
