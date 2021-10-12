#include "../inc/header.h"

void cleanup(void)
{
    SDL_DestroyRenderer(app.renderer);

    SDL_DestroyWindow(app.window);

    SDL_Quit();
}
