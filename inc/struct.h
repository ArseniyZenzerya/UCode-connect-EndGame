//
// Created by Ihor Zozulia on 29/09/2021.
//

#ifndef HACHIINU_STRUCT_H
#define HACHIINU_STRUCT_H

#include "header.h"

typedef struct {
    void (*logic)(void);
    void (*draw)(char *adress_for_back);
} Delegate;

struct textures {
    char name[MAX_NAME_LENGTH];
    SDL_Texture *texture;
    struct textures *next;
};

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
    struct textures textureHead, *textureTail;
} App;

struct Entity {
    float x;
    float y;
    int w;
    int h;
    float ex;
    float ey;
    float sx;
    float sy;
    float dx;
    float dy;
    int health;
    int isOnGround;
    float value;
    SDL_Texture *texture;
    void (*tick)(void);
    void (*touch)(struct Entity *other);
    long flags;
    struct Entity *riding;
    struct Entity *next;
};

typedef struct {
    SDL_Point camera;
    int map[MAP_WIDTH][MAP_HEIGHT];
    struct Entity entityHead, *entityTail;
    int collectTotal, collectFound;
} Stage;

typedef struct textures Texture;

#endif //HACHIINU_STRUCT_H
