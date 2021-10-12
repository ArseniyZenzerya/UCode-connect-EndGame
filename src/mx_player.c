#include "../inc/header.h"

static SDL_Texture *dog[2];

void initPlayer(char *way) {
    player = malloc(sizeof(struct Entity));
    memset(player, 0, sizeof(struct Entity));
    stage.entityTail->next = player;
    stage.entityTail = player;

    player->health = 1;


    char *allWayRight = (char *)malloc(sizeof(char *) * 30);
    strcpy(allWayRight, "resource/");
    strcat(allWayRight,way);
    strcat(allWayRight, "/idle1right.png");

    char *allWayLeft = (char *)malloc(sizeof(char *) * 30);// = (char *)malloc(sizeof(char *) * 30);
    strcpy(allWayLeft, "resource/");
    strcat(allWayLeft,way);
    strcat(allWayLeft, "/idle1left.png");

    dog[0] = loadTexture(allWayRight);
    dog[1] = loadTexture(allWayLeft);

    player->texture = dog[0];

    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

    free(allWayRight);
    free(allWayLeft);
}

void doPlayer() {
    player->dx = 0;

    if (app.keyboard[SDL_SCANCODE_A]) {
        player->dx = -PLAYER_MOVE_SPEED;

        player->texture = dog[1];
    }

    if (app.keyboard[SDL_SCANCODE_D]) {
        player->dx = PLAYER_MOVE_SPEED;

        player->texture = dog[0];
    }


    if (app.keyboard[SDL_SCANCODE_SPACE] && player->isOnGround) {
            player->dy = -11;

    }
}

    // if (app.keyboard[SDL_SCANCODE_R])
    // {
    //     player->x = player->y = 0;

    //     app.keyboard[SDL_SCANCODE_R] = 0;
    // }

