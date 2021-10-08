#include <stdint.h>

#pragma once

struct Position {
    union {
        struct {
            float x, y;
        };
        float pos[2];
    };
};

struct Movement {
    float speed;
    float acceleration;
};


struct Entity {
    // Each entity possesses a unique id
    uint64_t id; // 8
    // Human-readable name of an entity
    const char *name; // 8
    // Position of an entity
    Position pos; // 8
    // Associated texture for an entity
    SDL_Texture *texture; // 8

    // Callback for update method supposed to be called once per frame
    void (*update)(struct Entity *entity, float delta); // 8
};

