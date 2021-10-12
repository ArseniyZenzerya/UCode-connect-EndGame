#include "../inc/header.h"

SDL_Texture *fontTexture;
char drawTextBuffer[MAX_LINE_LENGTH];

enum
{
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};

void initFonts() {
    fontTexture = loadTexture("resource/font.png");
}

void drawText(int x, int y, int r, int g, int b, int align, char *format, ...) {
    int i, len, c;
    SDL_Rect rect;
    va_list args;

    memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

    va_start(args, format);
    vsprintf(drawTextBuffer, format, args);
    va_end(args);

    len = strlen(drawTextBuffer);

    switch (align) {
        case TEXT_RIGHT:
            x -= (len * GLYPH_WIDTH);
            break;

        case TEXT_CENTER:
            x -= (len * GLYPH_WIDTH) / 2;
            break;
    }

    rect.w = GLYPH_WIDTH;
    rect.h = GLYPH_HEIGHT;
    rect.y = 0;

    SDL_SetTextureColorMod(fontTexture, r, g, b);

    for (i = 0; i < len; i++) {
        c = drawTextBuffer[i];

        if (c >= ' ' && c <= 'Z') {
            rect.x = (c - ' ') * GLYPH_WIDTH;

            blitRect(fontTexture, &rect, x, y);

            x += GLYPH_WIDTH;
        }
    }
}

void drawHud() {
    SDL_Rect r;

    r.x = 0;
    r.y = 0;
    r.w = SCREEN_WIDTH;
    r.h = 35;

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 150);
    SDL_RenderFillRect(app.renderer, &r);
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

    drawText(SCREEN_WIDTH - 10, 5, 255, 255, 255, TEXT_RIGHT, "COIN %d/%d", stage.collectFound, stage.collectTotal);
}
