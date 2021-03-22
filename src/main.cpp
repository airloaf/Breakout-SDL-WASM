#include "Constants.h"
#include "Game.h"

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>

Uint32 timeSinceLastFrame;

void gameLoop(void *arg)
{
    Uint32 delta = SDL_GetTicks() - timeSinceLastFrame;
    ((Game *)arg)->tick(delta);
    timeSinceLastFrame = SDL_GetTicks();
}
#endif

int main(int argc, char *argv[])
{
    Game g("Breakout", WINDOW_WIDTH, WINDOW_HEIGHT);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(
        gameLoop, // function to call
        &g,
        0, // frame rate (0 = browser figures it out)
        1  // simulate infinite loop
    );
#else
    g.run();
#endif

    return 0;
}