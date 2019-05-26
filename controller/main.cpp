#include "../scenes/include_scenes.hpp"
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

#ifdef HOTRELOAD
#include <jet/live/Live.hpp>
#include <jet/live/Utility.hpp>
#include <jet/live/ILiveListener.hpp>

class ExampleListener : public jet::ILiveListener
{
public:
    void onLog(jet::LogSeverity severity, const std::string& message) override;
    void onCodePreLoad() override {};
    void onCodePostLoad() override {};
};

void ExampleListener::onLog(jet::LogSeverity severity, const std::string& message)
{
    std::string severityString;
    switch (severity) {
        case jet::LogSeverity::kInfo: severityString.append("[I]"); break;
        case jet::LogSeverity::kWarning: severityString.append("[W]"); break;
        case jet::LogSeverity::kError: severityString.append("[E]"); break;
        default: return;  // Skipping debug messages, they are too verbose
    }
    std::cout << severityString << ": " << message << std::endl;
}
#endif




int main(int argc, char* argv[])
{
    int windowWidth = 1280;
    int windowHeight = 720;

    const int minimalFPS = 6;
    const int maxFrameDelay = 1000/minimalFPS;
    const int maxFPS = 500;
    float deltaTime = 1; //init to 1 so that it can draw the first frame
    srand(time(NULL));

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(windowWidth, windowHeight, "[INSERT GAME NAME]");
    if(!IsWindowReady())
    {
        return 1;
    }

    SetTargetFPS(maxFPS);
    SetTraceLogLevel(LOG_INFO);
    SetTraceLogExit(LOG_WARNING);
    SetExitKey(0);

    fs::current_path("..");

    Scene* scene = new LevelSelect();

    #ifdef HOTRELOAD
    auto listener = jet::make_unique<ExampleListener>();
    auto live = jet::make_unique<jet::Live>(std::move(listener));

    while (!live->isInitialized()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        live->update();
    }
    live->update();
    #endif

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, FILTER_BILINEAR);

    while(scene)
    {
        float scale = std::min((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);
        deltaTime += GetFrameTime()*1000; // times 1000 so that it's in milliseconds

        if(deltaTime > 0)
        {
            if(deltaTime > maxFrameDelay)
            {
                deltaTime = maxFrameDelay; //it's the maximum delta time possible
                //so, if the game is under the minimal FPS, then, the game slows down
            }

            #ifdef HOTRELOAD
            live->update();

            if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_R))
            {
                live->tryReload();
            }
            #endif

            scene = scene->handleEvents(deltaTime);

            if(scene)
            {
                scene = scene->update(deltaTime);
                if(scene)
                {
                    BeginDrawing();

                        ClearBackground(BLACK);

                        BeginTextureMode(target);

                            ClearBackground((Color){ 30, 30, 30, 255 });

                            DrawFPS(0,0);
                            scene->render();

                        EndTextureMode();

                        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                           (Rectangle){ (float)((GetScreenWidth() - ((float)screenWidth*scale))*0.5), (float)((GetScreenHeight() - ((float)screenHeight*scale))*0.5),
                           (float)screenWidth*scale, (float)screenHeight*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);

                    EndDrawing();
                }
            }
            deltaTime = 0;
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); //here, if we have a deltaTime of 0, we wait a bit
        }
    }
    
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
