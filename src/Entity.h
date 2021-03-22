#pragma once

#include <SDL2/SDL.h>

#define PADDLE_ID 0
#define BALL_ID 1
#define BLOCK_ID 2

struct Vec
{
    union
    {
        float x;
        float w;
    };
    union
    {
        float y;
        float h;
    };
};

struct Transform
{
    Vec pos;
    Vec dim;
};

class Entity
{
public:
    Entity(Transform transform, unsigned int id);
    Entity(unsigned int id);
    ~Entity();

    Transform &getTransform();
    Vec &getVelocityVector();
    unsigned int getID();

private:
    Transform mTransform;
    Vec mVelocity;
    unsigned int mID;
};