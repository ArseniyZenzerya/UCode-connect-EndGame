#include "../inc/header.h"

int menu(SDL_Renderer* renderer) {

    SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, IMG_Load("resource/images/menu.png"));
    SDL_Rect background1_st;
    background1_st.x = 0;
    background1_st.y = 0;
    background1_st.w = SCREEN_WIDTH;
    background1_st.h = SCREEN_HEIGHT;

    bool running = true;
    int flag = 0;

    while (running) {
        SDL_RenderCopy(renderer, background, NULL, &background1_st);
        int x, y;
        Uint32 buttons;
        SDL_PumpEvents();
        buttons = SDL_GetMouseState(&x, &y);
        if (((buttons & SDL_BUTTON_LMASK) != 0) && x > 768 && x < 1152 && y > 565 & y < 650) { // up button
            running = false;
            flag = 1;
        }
        if (((buttons & SDL_BUTTON_LMASK) != 0) && x > 688 && x < 1252 && y > 685 & y < 755) { // midle button
            running = false;
            flag = 2;
        }
        if (((buttons & SDL_BUTTON_LMASK) != 0) && x > 880 && x < 1030 && y > 815 & y < 870) { /// down button
            running = false;
            SDL_DestroyTexture(background);
            exit(0);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(150);
    SDL_DestroyTexture(background);
    return flag;
}
