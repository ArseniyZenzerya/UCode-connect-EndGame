#include "../inc/header.h"

int menu_level(SDL_Renderer* renderer) {

    SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, IMG_Load("resource/images/MENU_LVL.png"));
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


        if (((buttons & SDL_BUTTON_LMASK) != 0) && x < 615) { // up button
            running = false;
            flag = 1;
        }
        if (((buttons & SDL_BUTTON_LMASK) != 0) && x > 635 && x < 1270) { /// down button
            running = false;
            flag = 2;
        }
        if (((buttons & SDL_BUTTON_LMASK) != 0) && x > 1270 && x < 1980) { /// down button
            running = false;
            flag = 3;
        }
        SDL_RenderPresent(renderer);

    }
    SDL_Delay(100);
    SDL_DestroyTexture(background);

    return flag;
}



