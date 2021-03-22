#include "Constants.h"
#include "Game.h"
#include "Physics.h"
#include "Renderer.h"

Game::Game(const std::string &title, int width, int height)
    : mWindowTitle(title),
      mWindowWidth(width),
      mWindowHeight(height),
      mQuit(false),
      mPaddle(PADDLE_TAG),
      mBall(BALL_TAG),
      mBoundary(BOUNDARY_TAG),
      mBallHold(true)
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
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_LEFT)
            {
                mPaddle.getVelocityVector().x = -PADDLE_SPEED;
            }
            else if (e.key.keysym.sym == SDLK_RIGHT)
            {
                mPaddle.getVelocityVector().x = PADDLE_SPEED;
            }
        }
        else if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_LEFT)
            {
                mPaddle.getVelocityVector().x = 0;
            }
            else if (e.key.keysym.sym == SDLK_RIGHT)
            {
                mPaddle.getVelocityVector().x = 0;
            }
            else if (e.key.keysym.sym == SDLK_SPACE)
            {
                if(mBallHold){
                    mBallHold = false;
                    mBall.getVelocityVector().x = BALL_SPEED;
                    mBall.getVelocityVector().y = -BALL_SPEED;
                }
            }
        }
    }
}

void Game::update(Uint32 delta)
{
    // Move Paddle
    updatePosition(delta, mPaddle);

    // Keep ball still if we are holding it
    if (mBallHold)
    {
        Transform paddlePos = mPaddle.getTransform();
        Transform &ballPos = mBall.getTransform();
        ballPos.pos.x = paddlePos.pos.x + (PADDLE_WIDTH / 2) - (BALL_WIDTH / 2);
        ballPos.pos.y = paddlePos.pos.y - (BALL_HEIGHT * 1.5);
        ballPos.dim.w = BALL_WIDTH;
        ballPos.dim.h = BALL_HEIGHT;
    }
    else
    {
        // Move Ball
        updatePosition(delta, mBall);

        // Check for block collisions
        std::list<Collision> blockCollisions = checkCollisions(mBlocks,
                                                               mBall);
        for (Collision col : blockCollisions)
        {
            mBall.getVelocityVector().y = -mBall.getVelocityVector().y;
            for(auto it = mBlocks.begin(); it != mBlocks.end(); it++){
                if(it->getID() == col.victimID){
                    mBlocks.erase(it);
                    break;
                }
            }
        }

        // Check for paddle collision
        Collision paddleCollision = checkCollision(mPaddle, mBall);
        if (paddleCollision.victimID == mPaddle.getID())
        {
            mBall.getVelocityVector().y = -mBall.getVelocityVector().y;
            mBall.getTransform().pos.y = mPaddle.getTransform().pos.y - (BALL_HEIGHT*1.5);
        }

        // Check for kill boundary collision
        Collision boundaryCollision = checkCollision(mBoundary, mBall);
        if (boundaryCollision.victimID == mBoundary.getID())
        {
            mBallHold = true;
        }
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);

    renderEntity(mRenderer, mPaddle);
    renderEntity(mRenderer, mBall);
    for (Entity block : mBlocks)
    {
        renderEntity(mRenderer, block);
    }

    SDL_RenderPresent(mRenderer);
}

void Game::generateLevel()
{
    Transform &paddlePos = mPaddle.getTransform();
    paddlePos.pos.x = WORLD_WIDTH / 2 - PADDLE_WIDTH / 2;
    paddlePos.pos.y = WORLD_HEIGHT - (PADDLE_HEIGHT * 1.5);
    paddlePos.dim.w = PADDLE_WIDTH;
    paddlePos.dim.h = PADDLE_HEIGHT;
    mPaddle.getVelocityVector().x = 0;
    mPaddle.getVelocityVector().y = 0;

    Transform &ballPos = mBall.getTransform();
    ballPos.pos.x = paddlePos.pos.x + (PADDLE_WIDTH / 2) - (BALL_WIDTH / 2);
    ballPos.pos.y = paddlePos.pos.y - (BALL_HEIGHT * 1.5);
    ballPos.dim.w = BALL_WIDTH;
    ballPos.dim.h = BALL_HEIGHT;
    mBall.getVelocityVector().x = 0;
    mBall.getVelocityVector().y = 0;

    // Create a boundary for killing the ball
    Transform &boundaryPos = mBoundary.getTransform();
    boundaryPos.pos.x = 0;
    boundaryPos.pos.y = WORLD_HEIGHT;
    boundaryPos.dim.w = WORLD_WIDTH * 2;
    boundaryPos.dim.h = WORLD_HEIGHT * 2;

    Transform blockPos;
    blockPos.dim.w = BLOCK_WIDTH;
    blockPos.dim.h = BLOCK_HEIGHT;

    for (float x = 0; x < WORLD_WIDTH; x += (BLOCK_WIDTH + BLOCK_SPACER_X))
    {
        for (float y = 0; y < WORLD_HEIGHT / 2; y += (BLOCK_HEIGHT + BLOCK_SPACER_Y))
        {
            blockPos.pos.x = x;
            blockPos.pos.y = y;

            Entity block(blockPos, BLOCK_TAG);
            block.getVelocityVector().x = 0;
            block.getVelocityVector().y = 0;
            mBlocks.push_back(block);
        }
    }
}