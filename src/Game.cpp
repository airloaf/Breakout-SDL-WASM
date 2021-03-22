#include "Constants.h"
#include "Game.h"
#include "Renderer.h"

#define FPS 60
#define FRAME_PERIOD (Uint32)(1000 / FPS)

Game::Game(const std::string &title, int width, int height)
    : mWindowTitle(title),
      mWindowWidth(width),
      mWindowHeight(height),
      mQuit(false),
      mPaddle(PADDLE_ID)
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

    Transform &t = mPaddle.getTransform();
    t.x = WORLD_WIDTH/2 - PADDLE_WIDTH/2;
    t.y = WORLD_HEIGHT - (PADDLE_HEIGHT*1.5);
    t.w = PADDLE_WIDTH;
    t.h = PADDLE_HEIGHT;
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
    Uint32 deltaTime = 0;
    while (!mQuit)
    {
        mFrameTime = SDL_GetTicks();

        tick(deltaTime);

        // Sleep if we need to
        if (deltaTime < FRAME_PERIOD)
        {
            SDL_Delay(FRAME_PERIOD - deltaTime);
        }

        // Calculate frame delta time
        deltaTime = SDL_GetTicks() - mFrameTime;
    }
}

void Game::tick(Uint32 delta)
{
    input();
    update(delta);
    render();
}

void Game::input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            mQuit = true;
        }
    }
}

void Game::update(Uint32 delta)
{
}

void Game::render()
{
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);

    renderEntity(mRenderer, mPaddle);

    SDL_RenderPresent(mRenderer);
}