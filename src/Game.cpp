#include "Constants.h"
#include "Game.h"
#include "Physics.h"
#include "Renderer.h"

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
    t.pos.x = WORLD_WIDTH/2 - PADDLE_WIDTH/2;
    t.pos.y = WORLD_HEIGHT - (PADDLE_HEIGHT*1.5);
    t.dim.w = PADDLE_WIDTH;
    t.dim.h = PADDLE_HEIGHT;
    mPaddle.getVelocityVector().x = 0;
    mPaddle.getVelocityVector().y = 0;

    generateLevel();
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
        else if(e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_LEFT)
            {
                mPaddle.getVelocityVector().x = -PADDLE_SPEED;
            }else if(e.key.keysym.sym == SDLK_RIGHT)
            {
                mPaddle.getVelocityVector().x = PADDLE_SPEED;
            }
        }
        else if(e.type == SDL_KEYUP)
        {
            mPaddle.getVelocityVector().x = 0;
        }
    }
}

void Game::update(Uint32 delta)
{
    updatePosition(delta, mPaddle);
}

void Game::render()
{
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);

    renderEntity(mRenderer, mPaddle);
    for(Entity block: mBlocks){
        renderEntity(mRenderer, block);
    }

    SDL_RenderPresent(mRenderer);
}

void Game::generateLevel()
{
    Transform blockPos;
    blockPos.dim.w = BLOCK_WIDTH;
    blockPos.dim.h = BLOCK_HEIGHT;

    for(float x = 0; x < WORLD_WIDTH; x += (BLOCK_WIDTH + BLOCK_SPACER_X))
    {
        for(float y = 0; y < WORLD_HEIGHT/2; y += (BLOCK_HEIGHT + BLOCK_SPACER_Y)) {
            blockPos.pos.x = x;
            blockPos.pos.y = y;

            mBlocks.push_back(Entity(blockPos, BLOCK_ID));
        }
    }

}