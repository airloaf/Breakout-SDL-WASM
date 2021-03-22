#include "Entity.h"

Entity::Entity(Transform transform, unsigned int id)
    : mTransform(transform), mID(id)
{
}

Entity::Entity(unsigned int id)
    : mID(id)
{
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

unsigned int Entity::getID()
{
    return mID;
}