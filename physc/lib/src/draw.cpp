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

void Drawing::drawCircle(Context *context, float radius) {
    b2Body* circle_body;
    b2BodyDef circle_body_def;
    circle_body_def.type = b2_dynamicBody;
    circle_body_def.position.Set(250, 250);
    b2Vec2 gravity_vec = context->contextWorld().GetGravity();
    circle_body = context->contextWorld().CreateBody(&circle_body_def);

    b2PolygonShape circle_shape;
    circle_shape.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixture_def;

    fixture_def.shape = &circle_shape;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3;
    circle_body->CreateFixture(&fixture_def);
    int velIter = 1;
    int posIter = 2;

    context->contextWorld().Step(1 / 200.0f, velIter, posIter);
}

