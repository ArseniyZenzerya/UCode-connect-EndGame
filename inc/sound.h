//
// Created by Ihor Zozulia on 10/2/21.
//

#ifndef HACHIINU_SOUND_H
#define HACHIINU_SOUND_H

enum {
    SND_COIN,
    SND_FINISH,
    SND_M
};

enum {
    CH_PLAYER,
    CH_POINT
};

void initSounds(char *level);
void loadMusic(char *filename);
void playMusic(int loop);
void playSound(int id, int channel);
void loadSounds(char *level);

#endif //HACHIINU_SOUND_H
