#include "../include/draw.h"

#include "../include/asset_loader.h"

#include "../include/render.h"


void Drawing::blit(Context* context, SDL_Texture* texture, int x, int y){
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);

    SDL_RenderCopy(context->context_renderer(), texture, NULL, &destination);
}

void Drawing::loadTextureAndBlit(Context* context, const char* path, int x, int y){
    SDL_Texture* texture;
    texture = AssetLoader::loadTexture(context->context_renderer(), path);
    if (!texture){
        SDL_LogMessage(1, SDL_LOG_PRIORITY_WARN, "%s\n", SDL_GetError());
        return;
    }
    blit(context, texture, x, y);
}

