#include "../include/draw.h"

#include "../include/asset_loader.h"

#include "../include/render.h"
#include "../include/broker.h"

static b2Vec2 triangle_vertices[3] = {
        {150, 150},
        {150,  200},
        {250, 150}
};

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

void Drawing::applyTransform(const b2Vec2* points) {

}

SDL_Point* Drawing::randomTriangleData() {
    return Broker::convert<b2Vec2, SDL_Point>(triangle_vertices, sizeof(triangle_vertices) / sizeof(triangle_vertices[0]));
}

// x0 - x coordinate of the center of a circle
// y0 - y coordinate of the center of a circle
SDL_Point* Drawing::drawCircle(SDL_Renderer* renderer, int32_t x0, int32_t y0, int32_t rad) {
    // (x - x0)^2 + (y - y0)^2 = r^2
    // (y - y0)^2 = r^2 - (x - x0)^2
    // y - y0 = sqrt(r^2 - (x-x0)^2)
    // y = y0 + sqrt(r^2 - (x-x0)^2)
    int32_t x, y;
    int32_t rad_sqr = rad * rad;

    for (x = -rad; x <= rad; x++){
        y = static_cast<int32_t>(sqrt(rad_sqr - ((x - x0) * (x - x0)))) + y0;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(renderer, x, y);
        SDL_RenderPresent(renderer);
    }
}

