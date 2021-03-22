#include "Renderer.h"
#include "Constants.h"

void renderEntity(SDL_Renderer *renderer, Entity &entity)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    Transform entityTransform = entity.getTransform();

    SDL_Rect renderRect;
    renderRect.x = entityTransform.pos.x * SCALE;
    renderRect.y = entityTransform.pos.y * SCALE;
    renderRect.w = entityTransform.dim.w * SCALE;
    renderRect.h = entityTransform.dim.h * SCALE;

    SDL_RenderFillRect(renderer, &renderRect);
}