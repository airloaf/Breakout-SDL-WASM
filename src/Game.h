#pragma once

#include <SDL2/SDL.h>
#include <string>

class Game
{
public:
    Game(const std::string &title, int width, int height);
    ~Game();

    void run();

private:
    void tick();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    std::string mWindowTitle;
    int mWindowWidth;
    int mWindowHeight;

    bool mQuit;

    Uint32 mFrameTime;
};