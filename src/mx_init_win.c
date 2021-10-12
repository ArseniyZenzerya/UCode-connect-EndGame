#include "../inc/header.h"

void initSDL(void) {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Couldn't initialize SDL Mixer\n");
        exit(1);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);

    app.window = SDL_CreateWindow("Hachi Inu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, windowFlags);

    if (!app.window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_ShowCursor(1);
}

void initGame(char *level, char *music) {
    initFonts();

    initSounds(level);

    loadMusic(music);

    playMusic(1);
}
