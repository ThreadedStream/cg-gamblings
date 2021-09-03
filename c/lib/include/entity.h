#include <stdint.h>

#pragma once

typedef struct Position {
    union {
        struct{
           float x, y;
        };
        float pos[2];
    };
} Position;

typedef struct Movement {
    float speed;
    float acceleration;
} Movement;


typedef struct Entity {
    // Each entity possesses a unique id
    uint32_t id;
    // Human-readable name of an entity
    const char *name;
    // Position of an entity
    Position pos;
    // Associated texture for an entity
    SDL_Texture *texture;

    // Callback for update method supposed to be called once per frame
    void (*update)(struct Entity *entity, float delta);
} Entity;

