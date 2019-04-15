#include "../scenes/level_select.hpp"
#include "../scenes/main_menu.hpp"
#include "../scenes/pause_menu.hpp"
#include "../scenes/sandbox.hpp"
#include "../components/components.hpp"

int main(int argc, char* argv[])
{
    int screenWidth = 1280;
    int screenHeight = 720;

    const int minimalFPS = 6;
    const int minimalFrameDelay = 1000/minimalFPS;
    const int maxFPS = 500;
    float deltaTime = 1; //init to 1 so that it can draw the first frame

    InitWindow(screenWidth, screenHeight, "[INSERT GAME NAME]");
    if(!IsWindowReady())
    {
        return 1;
    }

    SetTargetFPS(maxFPS);
    SetConfigFlags(FLAG_SHOW_LOGO | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    SetTraceLogLevel(LOG_DEBUG);
    SetTraceLogExit(LOG_WARNING);

    Scene* scene = new LevelSelect();


    while(scene)
    {
        deltaTime += GetFrameTime()*1000; // times 1000 so that it's in milliseconds

        if(deltaTime > 0)
        {
            if(deltaTime > minimalFPS)
            {
                deltaTime = minimalFrameDelay; //it's the maximum delta time possible
                //so, if the game is uder the minimal FPS, then, the game slows down
            }
            else
            {
                deltaTime = 0;
            }

            scene = scene->handleEvents(deltaTime);
            if(scene)
            {
                scene = scene->update(deltaTime);
                if(scene)
                {
                    scene->render();
                }
            }
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); //here, if we have a deltaTime of 0, we wait a bit
        }
    }

    CloseWindow();

    return 0;
}
