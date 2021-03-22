#include "Game.h"

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>

void gameLoop(void *arg)
{
    ((Game *)arg)->tick();
}
#endif

int main(int argc, char *argv[])
{
    Game g("Breakout", 1600, 900);

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