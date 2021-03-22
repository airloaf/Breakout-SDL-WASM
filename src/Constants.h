#pragma once

#define FPS                 60
#define FRAME_PERIOD        (Uint32)(1000 / FPS)

#define WINDOW_WIDTH        1280 
#define WINDOW_HEIGHT       720

#define SCALE               10

#define WORLD_WIDTH         (WINDOW_WIDTH/SCALE)
#define WORLD_HEIGHT        (WINDOW_HEIGHT/SCALE)

#define PADDLE_WIDTH        20
#define PADDLE_HEIGHT       2
#define PADDLE_SPEED        100

#define BLOCK_WIDTH         10
#define BLOCK_HEIGHT        2
#define BLOCK_SPACER_X      2
#define BLOCK_SPACER_Y      1

#define BALL_WIDTH          2
#define BALL_HEIGHT         2
#define BALL_SPEED          60