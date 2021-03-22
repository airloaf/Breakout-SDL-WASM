#include "Physics.h"

#include "Constants.h"

void boundPaddle(Entity &entity)
{
    Transform &transform = entity.getTransform();
    if((transform.pos.x + transform.dim.w) > WORLD_WIDTH) {
        transform.pos.x = WORLD_WIDTH - transform.dim.w;
    }else if(transform.pos.x < 0){
        transform.pos.x = 0;
    }
}

void updatePosition(Uint32 delta, Entity &entity)
{
    float deltaTime = (float)delta / 1000.0f;
    Transform &transform = entity.getTransform();
    Vec &vel = entity.getVelocityVector();

    transform.pos.x = transform.pos.x + (vel.x * deltaTime);
    transform.pos.y = transform.pos.y + (vel.y * deltaTime);

    if (entity.getID() == PADDLE_ID)
    {
        boundPaddle(entity);
    }
}