#include "Physics.h"

#include "Constants.h"

void boundPaddle(Entity &entity)
{
    Transform &transform = entity.getTransform();
    if ((transform.pos.x + transform.dim.w) > WORLD_WIDTH)
    {
        transform.pos.x = WORLD_WIDTH - transform.dim.w;
    }
    else if (transform.pos.x < 0)
    {
        transform.pos.x = 0;
    }
}

void boundBall(Entity &entity)
{
    Transform &transform = entity.getTransform();
    if ((transform.pos.x + transform.dim.w) > WORLD_WIDTH)
    {
        transform.pos.x = WORLD_WIDTH - transform.dim.w;
        entity.getVelocityVector().x = -entity.getVelocityVector().x;
    }
    else if (transform.pos.x < 0)
    {
        transform.pos.x = 0;
        entity.getVelocityVector().x = -entity.getVelocityVector().x;
    }
    else if (transform.pos.y < 0)
    {
        transform.pos.y = 0;
        entity.getVelocityVector().y = -entity.getVelocityVector().y;
    }
}

void updatePosition(Uint32 delta, Entity &entity)
{
    float deltaTime = (float)delta / 1000.0f;
    Transform &transform = entity.getTransform();
    Vec &vel = entity.getVelocityVector();

    transform.pos.x = transform.pos.x + (vel.x * deltaTime);
    transform.pos.y = transform.pos.y + (vel.y * deltaTime);

    if (entity.getTag() == PADDLE_TAG)
    {
        boundPaddle(entity);
    }
    else if (entity.getTag() == BALL_TAG)
    {
        boundBall(entity);
    }
}

Collision checkCollision(Entity &victim, Entity &hitter)
{
    Collision c;
    c.victimID = -1;
    c.hitterID = -1;

    Transform &vTrans = victim.getTransform();
    Transform &hTrans = hitter.getTransform();

    if (
        hTrans.pos.x < vTrans.pos.x + vTrans.dim.w &&
        hTrans.pos.x + hTrans.dim.w > vTrans.pos.x &&
        hTrans.pos.y < vTrans.pos.y + vTrans.dim.h &&
        hTrans.pos.y + hTrans.dim.h > vTrans.pos.y)
    {
        c.victimID = victim.getID();
        c.hitterID = hitter.getID();
    }

    return c;
}

std::list<Collision> checkCollisions(std::list<Entity> &victims,
                                     Entity &hitter)
{
    std::list<Collision> hits;

    for (auto victim: victims)
    {
        Collision c = checkCollision(victim, hitter);
        if (c.victimID != -1)
        {
            hits.push_back(c);
        }
    }

    return hits;
}