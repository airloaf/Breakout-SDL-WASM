#include "Game.h"

#define FPS 60
#define FRAME_PERIOD (Uint32)(1000 / FPS)

Game::Game(const std::string &title, int width, int height)
    : mWindowTitle(title),
      mWindowWidth(width),
      mWindowHeight(height),
      mQuit(false)
{
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create window and renderer
    mWindow = SDL_CreateWindow(title.c_str(),
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               width,
                               height,
                               SDL_WINDOW_SHOWN);
    mRenderer = SDL_CreateRenderer(mWindow,
                                   -1,
                                   SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
}

Game::~Game()
{
    // Destroy renderer and window
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    // Quit SDL
    SDL_Quit();
}

void Game::run()
{
    while (!mQuit)
    {
        mFrameTime = SDL_GetTicks();

        tick();

        // Calculate frame delta time
        Uint32 deltaTime = SDL_GetTicks() - mFrameTime;

        // Sleep if we need to
        if (deltaTime < FRAME_PERIOD)
        {
            SDL_Delay(FRAME_PERIOD - deltaTime);
        }
    }
}

void Game::tick()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            mQuit = true;
        }
    }
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);
}