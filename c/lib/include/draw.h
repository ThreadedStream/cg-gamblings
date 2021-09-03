#include "render.h"
#include <unistd.h>
#include "asset_loader.h"

#pragma once

void blit(struct ContextGraphique* context, SDL_Texture* texture, int x, int y);

void loadTextureAndBlit(struct ContextGraphique* context, const char* path, int x, int y);


