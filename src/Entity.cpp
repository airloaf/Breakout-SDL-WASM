#include "Entity.h"

static unsigned int id = 0;

Entity::Entity(Transform transform, unsigned int tag)
    : mTransform(transform), mTag(tag)
{
    mID = id++;
}

Entity::Entity(unsigned int tag)
    : mTag(tag)
{
    mID = id++;
}

Entity::~Entity()
{
}

Transform &Entity::getTransform()
{
    return mTransform;
}

Vec &Entity::getVelocityVector()
{
    return mVelocity;
}

unsigned int Entity::getTag()
{
    return mTag;
}

unsigned int Entity::getID()
{
    return mID;
}