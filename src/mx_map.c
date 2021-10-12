#include "../inc/header.h"

static SDL_Texture *tiles[MAX_TILES];

void initMap(char *adress, char *level) {
    memset(&stage.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);

    loadTiles(level);

    prepareScene();

    loadMap(adress);
}

void drawMap(void) {
    int x, y, n, x1, x2, y1, y2, mx, my;

    x1 = (stage.camera.x % TILE_SIZE) * -1;
    x2 = x1 + MAP_RENDER_WIDTH * TILE_SIZE + (x1 == 0 ? 0 : TILE_SIZE);

    y1 = (stage.camera.y % TILE_SIZE) * -1;
    y2 = y1 + MAP_RENDER_HEIGHT * TILE_SIZE + (y1 == 0 ? 0 : TILE_SIZE);

    mx = stage.camera.x / TILE_SIZE;
    my = stage.camera.y / TILE_SIZE;

    for (y = y1; y < y2; y += TILE_SIZE) {
        for (x = x1; x < x2; x += TILE_SIZE) {
            if (mx >= 0 && my >= 0 && mx < MAP_WIDTH && my < MAP_HEIGHT) {
                n = stage.map[mx][my];

                if (n > 0) {
                    blit(tiles[n], x, y, 0);
                }
            }
            mx++;
        }
        mx = stage.camera.x / TILE_SIZE;
        my++;
    }
}

void loadTiles(char *level) {
    int i;
    char filename[MAX_FILENAME_LENGTH];

    for (i = 1 ; i < MAX_TILES ; i++)
    {
        sprintf(filename, "resource/%s/tile%d.png", level, i);

        tiles[i] = loadTexture(filename);
    }
}

void loadMap(const char *filename) {
    char *data, *p;
    int x, y;

    data = readFile(filename);

    p = data;

    for (y = 0 ; y < MAP_HEIGHT ; y++)
    {
        for (x = 0 ; x < MAP_WIDTH ; x++)
        {
            sscanf(p, "%d", &stage.map[x][y]);

            do {p++;} while (*p != ' ' && *p != '\n');
        }
    }

    free(data);
}

int isInsideMap(int x, int y)
{
    return x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT;
}
