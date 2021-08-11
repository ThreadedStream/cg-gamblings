#include "draw.h"


void blit(struct ContextGraphique* context, SDL_Texture* texture, int x, int y){
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);

    SDL_RenderCopy(context->renderer, texture, NULL, &destination);
}

void loadTextureAndBlit(struct ContextGraphique* context, const char* path, int x, int y){
    SDL_Texture* texture;
    texture = loadTexture(context, path);
    if (!texture){
        SDL_LogMessage(1, SDL_LOG_PRIORITY_WARN, "%s\n", SDL_GetError());
        return;
    }
    blit(context, texture, x, y);
}

