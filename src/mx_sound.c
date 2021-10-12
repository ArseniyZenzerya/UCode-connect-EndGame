#include "../inc/header.h"

Mix_Chunk *sounds[SND_M];
Mix_Music *music;

void initSounds(char *level) {
    memset(sounds, 0, sizeof(Mix_Chunk * ) * SND_M);

    music = NULL;

    loadSounds(level);
}

void loadMusic(char *filename) {
    if (music != NULL) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }

    music = Mix_LoadMUS(filename);
}

void playMusic(int loop) {
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel) {
    Mix_PlayChannel(channel, sounds[id], 0);
}

void loadSounds(char *level) {
    char *allWayFound = (char *)malloc(sizeof(char *) * 35);
    strcpy(allWayFound, "resource/");
    strcat(allWayFound,level);
    strcat(allWayFound, "/sound/found_item.ogg");


    char *allWayFinish = (char *)malloc(sizeof(char *) * 35);
    strcpy(allWayFinish, "resource/");
    strcat(allWayFinish,level);
    strcat(allWayFinish, "/sound/fanfare.ogg");

    sounds[SND_COIN] = Mix_LoadWAV(allWayFound);
    sounds[SND_FINISH] = Mix_LoadWAV(allWayFinish);

    free(allWayFinish);
    free(allWayFound);
}

