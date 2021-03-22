#pragma once

#include <SDL2/SDL.h>

#define PADDLE_ID   0
#define BALL_ID     1
#define BLOCK_ID    2

struct Transform {
    float x, y;
    float w, h;
};

class Entity
{
public:
    Entity(Transform transform, unsigned int id);
    Entity(unsigned int id);
    ~Entity();

    Transform &getTransform();
    unsigned int getID();

private:
    Transform mTransform;
    unsigned int mID;
};