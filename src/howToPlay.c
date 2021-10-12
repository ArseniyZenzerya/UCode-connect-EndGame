#include "../inc/header.h"



void howToPlay() {

    SDL_Texture *background_pl = loadTexture("resource/howToPlay.png");
    SDL_Rect background_howplay;
    background_howplay.x = 0;
    background_howplay.y = 0;
    background_howplay.w = SCREEN_WIDTH;
    background_howplay.h = SCREEN_HEIGHT;

    SDL_RenderCopy(app.renderer, background_pl, NULL, &background_howplay);

    SDL_RenderPresent(app.renderer);

    prepareScene();
    SDL_Delay(1500);

    if (menu(app.renderer) == 1) {
        switch_lvl();
    } else if (menu(app.renderer) == 2) {
        howToPlay();
    }
}
