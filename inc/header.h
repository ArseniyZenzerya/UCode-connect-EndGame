#ifndef ENDGAME_H
#define ENDGAME_H

#define SCREEN_WIDTH          1920
#define SCREEN_HEIGHT         1080

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'

#define PLAYER_MOVE_SPEED      3
#define PLATFORM_SPEED         6

#define MAX_TILES              10

#define TILE_SIZE              32

#define MAP_WIDTH              90
#define MAP_HEIGHT             47

#define MAP_RENDER_WIDTH       60
#define MAP_RENDER_HEIGHT      34

#define MAX_NAME_LENGTH        32
#define MAX_LINE_LENGTH        1024
#define MAX_FILENAME_LENGTH    1024

#define MAX_KEYBOARD_KEYS      350

#define MAX_SND_CHANNELS       8

#define GLYPH_WIDTH            18
#define GLYPH_HEIGHT           29

#define EF_NONE       0
#define EF_WEIGHTLESS (2 << 0)
#define EF_SOLID      (2 << 1)
#define EF_PUSH       (2 << 2)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "struct.h"
#include "sound.h"

void cleanup();
void initSDL();
void prepareScene();
void presentScene();
void doInput();
void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
void blit(SDL_Texture *texture, int x, int y, int center);
void doKeyUp(SDL_KeyboardEvent *event);
void doKeyDown(SDL_KeyboardEvent *event);
char *readFile(const char *filename);
void initMap(char *adress, char *level);
void drawMap();
void loadTiles(char *level);
void loadMap(const char *filename);
void initStage(char *adress, char *level, char *entity, char *coinLevel);
void logic();
void draw(char *adress_background);
void capFrameRate(long *then, float *remainder);
void initGame(char *level, char *music);
SDL_Texture *loadTexture(char *filename);
SDL_Texture *getTexture(char *name);
void addTextureToCache(char *name, SDL_Texture *sdlTexture);
void doCamera();
void doPlayer();
void doEntities();
void move(struct Entity *e);
void moveToWorld(struct Entity *e, float dx, float dy);
void drawEntities();
void initPlayer(char *way);
void doPlayer();
void initEntities(char *level, char *coinLevel);
int isInsideMap(int x, int y);
void moveToEntities(struct Entity *e, float dx, float dy);
void loadEnts(const char *filename, char *coinLevel);
void addEntFromLine(char *line, char *coinLevel);
int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void push(struct Entity *e, float dx, float dy);
void initPlatform(char *line);
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
void touch(struct Entity *other);
void initCoin(char *line, char *coinLevel);
void drawHud();
void initFonts();
void howToPlay();

int menu_level(SDL_Renderer* renderer);
int menu(SDL_Renderer* renderer);
void switch_lvl();
void initializathion_map(char * adress_map, char * adress_back, char * back_for_vic, int levelNum, char *level, char *entity, char *coinLevel);
struct Entity *player;

struct Entity *self;

Stage stage;

App app;

#endif
