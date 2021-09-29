#pragma once

#include "scene.h"

class LightingScene : Scene {
public:
    LightingScene() {}



private:
    void prepareBufferObjects() override;

    void prepareTextureData() override;

private:
};