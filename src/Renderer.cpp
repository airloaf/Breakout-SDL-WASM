#include "Renderer.h"
#include "Constants.h"

void renderEntity(SDL_Renderer *renderer, Entity &entity)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    Transform entityTransform = entity.getTransform();

    SDL_Rect renderRect;
    renderRect.x = entityTransform.x * SCALE;
    renderRect.y = entityTransform.y * SCALE;
    renderRect.w = entityTransform.w * SCALE;
    renderRect.h = entityTransform.h * SCALE;

    SDL_RenderFillRect(renderer, &renderRect);
}