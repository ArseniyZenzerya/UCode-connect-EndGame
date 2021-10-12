#include "../inc/header.h"

void tick1(void);

void initCoin(char *line, char *coinLevel) {
    struct Entity *e;

    e = malloc(sizeof(struct Entity));
    memset(e, 0, sizeof(struct Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    sscanf(line, "%*s %f %f", &e->x, &e->y);

    e->health = 1;

    char *coin = (char *) malloc(sizeof(char *) * 35);
    strcpy(coin, "resource/");
    strcat(coin, coinLevel);
    strcat(coin, "/coin.png");

    e->texture = loadTexture(coin);
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->flags = EF_WEIGHTLESS;
    e->tick = tick1;
    e->touch = touch;

    stage.collectTotal++;
}

void tick1(void)
{
    self->value += 0.1;

    self->y += sin(self->value);
}

void touch(struct Entity *other) {
    if (self->health > 0 && other == player) {
        self->health--;
        stage.collectFound++;

        if (stage.collectFound == stage.collectTotal)
        {
            playSound(SND_FINISH, CH_POINT);
        }
        else
        {
            playSound(SND_COIN, CH_POINT);
        }
    }
}

