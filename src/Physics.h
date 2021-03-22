#pragma once

#include "Entity.h"

#include <SDL2/SDL.h>

#include <list>

struct Collision
{
    unsigned int hitterID;
    unsigned int victimID;
};

void updatePosition(Uint32 delta, Entity &entity);

Collision checkCollision(Entity &victim, Entity &hitter);

std::list<Collision> checkCollisions(std::list<Entity> &victims,
                                     Entity &hitter);