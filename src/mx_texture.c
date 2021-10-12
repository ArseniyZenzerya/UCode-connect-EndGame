#include "../inc/header.h"

void addTextureToCache(char *name, SDL_Texture *sdlTexture)
{
    Texture *texture;

    texture = malloc(sizeof(Texture));
    memset(texture, 0, sizeof(Texture));
    app.textureTail->next = texture;
    app.textureTail = texture;

    STRNCPY(texture->name, name, MAX_NAME_LENGTH);
    texture->texture = sdlTexture;
}

SDL_Texture *loadTexture(char *filename)
{
    SDL_Texture *texture;

    texture = getTexture(filename);

    if (texture == NULL)
    {
        texture = IMG_LoadTexture(app.renderer, filename);
        addTextureToCache(filename, texture);
    }

    return texture;
}

SDL_Texture *getTexture(char *name)
{
    Texture *t;

    for (t = app.textureHead.next ; t != NULL ; t = t->next)
    {
        if (strcmp(t->name, name) == 0)
        {
            return t->texture;
        }
    }

    return NULL;
}
