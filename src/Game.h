#pragma once

#include "Entity.h"

#include <SDL2/SDL.h>
#include <string>

class Game
{
public:
    Game(const std::string &title, int width, int height);
    ~Game();

    void run();

#ifndef EMSCRIPTEN
private:
#endif
    void tick(Uint32 delta);
#ifdef EMSCRIPTEN
private:
#endif

    void input();
    void update(Uint32 delta);
    void render();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    std::string mWindowTitle;
    int mWindowWidth;
    int mWindowHeight;

    bool mQuit;

    Uint32 mFrameTime;

    Entity mPaddle;
};