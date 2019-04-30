#pragma once
#include "../scene.hpp"
#include "../../data-layer/jsonParser.hpp"

class Lesson: public Scene {
    public:
        Lesson(std::string path);
        Lesson(std::string path, CacheManager* cacheManager);
        Scene* handleEvents(float deltaTime) override;
        Scene* update(float deltaTime) override;
        void render() const override;
        ~Lesson();

        friend class JsonParser;

    private:
        Font font;
        std::string text;
        Rectangle rect;
        rj::Document doc;
        JsonParser parser;
        CacheManager* cacheManager;
        Event nextEvent;
};
