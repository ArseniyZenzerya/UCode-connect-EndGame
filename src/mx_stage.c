#include "../inc/header.h"

void initStage(char *adress, char *level, char *entity, char *coinLevel) {
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    prepareScene();

    initMap(adress, level);

    stage.entityTail = &stage.entityHead;

    initEntities(entity, coinLevel);

    initPlayer(level);
}

void logic(void)
{
    doPlayer();

    doCamera();

    doEntities();
}

void draw(char *adress_background) {
    prepareScene();
    SDL_Texture *background = loadTexture(adress_background);
    SDL_Rect background1_st;
    background1_st.x = 0;
    background1_st.y = 0;
    background1_st.w = SCREEN_WIDTH;
    background1_st.h = SCREEN_HEIGHT;

    SDL_RenderCopy(app.renderer, background, NULL, &background1_st);

    drawMap();

    drawEntities();

    drawHud();
}

void capFrameRate(long *then, float *remainder)
{
    long wait, frameTime;

    wait = 16 + *remainder;

    *remainder -= (int)*remainder;

    frameTime = SDL_GetTicks() - *then;

    wait -= frameTime;

    if (wait < 1)
    {
        wait = 1;
    }

    SDL_Delay(wait);

    *remainder += 0.667;

    *then = SDL_GetTicks();
}
