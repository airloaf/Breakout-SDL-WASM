#pragma once

#include <SDL2/SDL.h>

#define PADDLE_TAG      0
#define BALL_TAG        1
#define BLOCK_TAG       2
#define BOUNDARY_TAG    3

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
    Entity(Transform transform, unsigned int tag);
    Entity(unsigned int tag);
    ~Entity();

    Transform &getTransform();
    Vec &getVelocityVector();
    unsigned int getTag();
    unsigned int getID();

private:
    Transform mTransform;
    Vec mVelocity;
    unsigned int mTag;
    unsigned int mID;
};