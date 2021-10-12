#include "../inc/header.h"

void prepareScene(void)
{
    //SDL_SetRenderDrawColor(app.renderer, 96, 0, 120, 255);
    //menu_level(app.renderer);
    SDL_RenderClear(app.renderer);
}

void presentScene(void) {
    // menu_level(app.renderer);
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderPresent(app.renderer);
}

void blit(SDL_Texture *texture, int x, int y, int center)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    if (center)
    {
        dest.x -= dest.w / 2;
        dest.y -= dest.h / 2;
    }

    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;
    SDL_RenderCopy(app.renderer, texture, src, &dest);
}

void drawEntities(void)
{
    struct Entity *e;

    for (e = stage.entityHead.next ; e != NULL ; e = e->next)
    {
        blit(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, 0);
       
    } 
}

void addEntFromLine(char *line, char *coinLevel){
    char name[MAX_NAME_LENGTH];
    struct Entity *e;

    e = malloc(sizeof(struct Entity));
    memset(e, 0, sizeof(struct Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    sscanf(line, "%s", name);

    if (strcmp(name, "BLOCK") == 0) {
        sscanf(line, "%*s %f %f", &e->x, &e->y);

        e->texture = loadTexture("gfx/block.png");
        SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
        e->flags = EF_SOLID + EF_WEIGHTLESS;
    } else if (strcmp(name, "PLATFORM") == 0) {
        initPlatform(line);
    } else if (strcmp(name, "COIN") == 0) {
        initCoin(line, coinLevel);
    } else {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Unknown entity '%s'", line);
    }
}

