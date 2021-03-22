#pragma once

#include "Entity.h"

#include <SDL2/SDL.h>

#include <string>
#include <list>

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

    void generateLevel();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    std::string mWindowTitle;
    int mWindowWidth;
    int mWindowHeight;

    bool mQuit;

    Uint32 mFrameTime;

    Entity mPaddle;
    Entity mBall;
    Entity mBoundary;
    std::list<Entity> mBlocks;

    bool mBallHold;
};