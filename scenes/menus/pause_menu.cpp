#include "pause_menu.hpp"
#include "level_select.hpp"

void PauseMenu::initButtons()
{
    auto view = registry->view<button>();
    for(auto entity : view)
    {
        registry->destroy(entity);
    }

    int width = screenWidth;
    int widthBox = 500;
    int heightBox = 65;
    int padding = 30;
    for(int i = 0; i < size; ++i)
    {
        auto entity = registry->create();

        auto& btn = registry->assign<button>(entity, cacheManager->textures.handle(entt::HashedString{"buttons"}), cacheManager->animations.handle(entt::HashedString{"buttons"}));
        btn.rect.x = width/2 - widthBox/2;
        btn.rect.y = (heightBox+padding)*i + padding;
        btn.rect.width = widthBox;
        btn.rect.height = heightBox;
        if(i == 0)
        {
            btn.text = "Resume Game";
        }
        else if(i == 1)
        {
            btn.text = "Main Menu";
        }
        else if(i == 2)
        {
            btn.text = "Level Select";
        }
        else if(i == 3)
        {
            btn.text = "Options";
        }
        else if(i == 4)
        {
            btn.text = "Help";
        }
        btn.selected = false;
        btn.color = WHITE;
        btn.id = i;
    }
    std::cout << "number of entities: " << registry->size() << std::endl;
}

PauseMenu::PauseMenu(Scene* resumeScene): resumeScene(resumeScene), selected(0), size(5)
{
    registry = new entt::DefaultRegistry{};
    cacheManager = new CacheManager;
    font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    cacheManager->animations.load<animationLoader>(entt::HashedString{"buttons"}, "data/assets/buttons/button_active", 1000);
    cacheManager->textures.load<textureLoader>(entt::HashedString{"buttons"}, "data/assets/buttons/button_inactive.png");
    cacheManager->audios.load<soundFXLoader>(entt::HashedString{"select"}, "data/sound/select.wav");
    cacheManager->audios.load<soundFXLoader>(entt::HashedString{"back"}, "data/sound/back.wav");

    camera.target = {(float) GetScreenWidth()/2,(float) GetScreenHeight()/2};
    camera.offset = {0,0};
    camera.rotation = 0.f;
    camera.zoom = 1.f;
    
    initButtons();
}

PauseMenu::PauseMenu(Scene* resumeScene, CacheManager* cacheManager): resumeScene(resumeScene), cacheManager(cacheManager), selected(0), size(5)
{
    registry = new entt::DefaultRegistry{};
    cacheManager->animations.load<animationLoader>(entt::HashedString{"buttons"}, "data/assets/buttons/button_active", 1000);
    cacheManager->textures.load<textureLoader>(entt::HashedString{"buttons"}, "data/assets/buttons/button_inactive.png");
    font = LoadFontEx("data/fonts/Anonymous Pro.ttf", 40, NULL, 600);
    cacheManager->audios.load<soundFXLoader>(entt::HashedString{"select"}, "data/sound/select.wav");
    cacheManager->audios.load<soundFXLoader>(entt::HashedString{"back"}, "data/sound/back.wav");

    camera.target = {(float) GetScreenWidth()/2,(float) GetScreenHeight()/2};
    camera.offset = {0,0};
    camera.rotation = 0.f;
    camera.zoom = 1.f;
    
    initButtons();
}

Scene* PauseMenu::handleEvents(float deltaTime)
{
    if(WindowShouldClose())
    {
        delete resumeScene;
        delete this;
        return nullptr;
    }
    if(IsKeyPressed(KEY_F11))
    {
        systems::toggleFullscreen();
        camera.target = {(float) GetScreenWidth()/2,(float) GetScreenHeight()/2};
        initButtons();
    }

    if(IsKeyPressed(KEY_UP))
    {
        selected--;
    }
    if(IsKeyPressed(KEY_DOWN))
    {
        selected++;
    }

    Vector2 newMousePos = GetMousePosition();
    if(Vector2Distance(mousePos, newMousePos))
    {
        mousePos = newMousePos;
        mouseActive = true;
    }
    else
    {
        mouseActive = false;
    }

    //camera.offset.y += GetMouseWheelMove()*50;

    //int height = GetScreenHeight();
    //int heightBox = 50;
    //int padding = 30;
    //if(-((size-1)*(heightBox+padding)+ padding) - (heightBox + padding)+ height < 0)
    //{
    //    if(camera.offset.y > 0)
    //    {
    //        camera.offset.y = 0;
    //    }
    //    else if(camera.offset.y < -((size-1)*(heightBox+padding)+ padding) - (heightBox + padding)+ height)
    //    {
    //        camera.offset.y = -((size-1)*(heightBox+padding)+ padding) - (heightBox + padding)+ height;
    //    }
    //}

    Scene* tmp;
    if(IsKeyPressed(KEY_ESCAPE))
    {
        PlaySound(cacheManager->audios.handle(entt::HashedString{"back"})->audio);
        tmp = resumeScene;
        delete this;
        return tmp;
    }
    
    if(IsKeyPressed(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && systems::checkCollisionMouseButtons(registry, mousePos)))
    {
        PlaySound(cacheManager->audios.handle(entt::HashedString{"select"})->audio);
        switch(selected)
        {
            case 0:
                tmp = resumeScene;
                delete this;
                return tmp;
                break;
            case 1:
                break;
            case 2:
                delete resumeScene;
                delete this;
                return new LevelSelect;
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                break;
        }
        if(selected == 2)
        {
            delete resumeScene;
            delete this;
            return new LevelSelect;
        }
    }

    return this;
}

Scene* PauseMenu::update(float deltaTime)
{
    if(selected < 0)
    {
        selected = (int) size -1;
    }
    else if(selected >= (int) size)
    {
        selected = 0;
    }
    systems::updateAnims(registry, 0, deltaTime);
    systems::updatePos(registry, deltaTime);
    selected = systems::updateButtons(registry, mousePos, mouseActive, selected );
    return this;
}

void PauseMenu::render() const
{
    float fontSize = 40;
    float spacing = 0;

    systems::drawEntities(registry);

    BeginMode2D(camera);
        systems::drawButtons(registry, font, fontSize, spacing);
    EndMode2D();
}

PauseMenu::~PauseMenu()
{
    UnloadFont(font);
}
