#include "../inc/header.h"

void tick(void);

void initEntities(char *level, char *coinLevel) {
    loadEnts(level, coinLevel);
}

void doEntities(void) {
    struct Entity *e, *prev;

    prev = &stage.entityHead;

    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        self = e;

        if (e->tick) {
            e->tick();
        }

        move(e);

        if (e->health <= 0) {
            if (e == stage.entityTail) {
                stage.entityTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }

    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        if (e->riding != NULL) {
            e->x += e->riding->dx;

            push(e, e->riding->dx, 0);
        }

        e->x = MIN(MAX(e->x, 0), MAP_WIDTH * TILE_SIZE);
        e->y = MIN(MAX(e->y, 0), MAP_HEIGHT * TILE_SIZE);
    }
}

void move(struct Entity *e)
{
    if (!(e->flags & EF_WEIGHTLESS))
    {
        e->dy += 1.5;
        e->dy = MAX(MIN(e->dy, 18), -999);
    }
    if (e->riding != NULL && e->riding->dy > 0)
    {
        e->dy = e->riding->dy + 1;
    }
    e->isOnGround = 0;
    e->x += e->dx;
    moveToWorld(e, e->dx, 0);
    moveToEntities(e, e->dx, 0);
    e->y += e->dy;
    moveToWorld(e, 0, e->dy);
    moveToEntities(e, 0, e->dy);
    e->x = MIN(MAX(e->x, 0), MAP_WIDTH * TILE_SIZE);
    e->y = MIN(MAX(e->y, 0), MAP_HEIGHT * TILE_SIZE);
}

void push(struct Entity *e, float dx, float dy)
{
    moveToWorld(e, dx, dy);

    moveToEntities(e, dx, dy);
}

void moveToWorld(struct Entity *e, float dx, float dy) {
    int mx, my, hit, adj;

    if (dx != 0) {
        e->x += dx;

        mx = dx > 0 ? (e->x + e->w) : e->x;
        mx /= TILE_SIZE;

        my = (e->y / TILE_SIZE);

        hit = 0;

        if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
            hit = 1;
        }

        my = (e->y + e->h - 1) / TILE_SIZE;

        if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
            hit = 1;
        }

        if (hit) {
            adj = dx > 0 ? -e->w : TILE_SIZE;

            e->x = (mx * TILE_SIZE) + adj;

            e->dx = 0;
        }
    }

    if (dy != 0) {
        e->y += dy;

        my = dy > 0 ? (e->y + e->h) : e->y;
        my /= TILE_SIZE;

        mx = e->x / TILE_SIZE;

        hit = 0;

        if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
            hit = 1;
        }

        mx = (e->x + e->w - 1) / TILE_SIZE;

        if (!isInsideMap(mx, my) || stage.map[mx][my] != 0) {
            hit = 1;
        }

        if (hit) {
            adj = dy > 0 ? -e->h : TILE_SIZE;

            e->y = (my * TILE_SIZE) + adj;

            e->dy = 0;

            e->isOnGround = dy > 0;
        }
    }
}

void moveToEntities(struct Entity *e, float dx, float dy) {
    struct Entity *other;
    int adj;

    for (other = stage.entityHead.next; other != NULL; other = other->next) {
        if (other != e && collision(e->x, e->y, e->w, e->h, other->x, other->y, other->w, other->h)) {
            if (other->flags & EF_SOLID) {
                if (dy != 0) {
                    adj = dy > 0 ? -e->h : other->h;

                    e->y = other->y + adj;

                    e->dy = 0;

                    if (dy > 0) {
                        e->isOnGround = 1;

                        e->riding = other;
                    }
                }

                if (dx != 0) {
                    adj = dx > 0 ? -e->w : other->w;

                    e->x = other->x + adj;

                    e->dx = 0;
                }
            } else if (e->flags & EF_PUSH) {
                other->x += e->dx;
                push(other, e->dx, 0);

                other->y += e->dy;
                push(other, 0, e->dy);
            }

            if (e->touch) {
                e->touch(other);
            }
        }
    }
}

void loadEnts(const char *filename, char *coinLevel) {
    char line[MAX_LINE_LENGTH];
    char *data, *p;
    int n;

    data = readFile(filename);

    p = data;

    n = 0;

    memset(line, '\0', MAX_LINE_LENGTH);

    while (*p) {
        if (*p == '\n') {
            addEntFromLine(line, coinLevel);
            memset(line, '\0', MAX_LINE_LENGTH);
            n = 0;
        } else {
            line[n++] = *p;
        }

        p++;
    }

    free(data);
}

void tick(void) {
    if (fabsf(self->x - self->sx) < PLATFORM_SPEED && fabsf(self->y - self->sy) < PLATFORM_SPEED) {
        calcSlope(self->ex, self->ey, self->x, self->y, &self->dx, &self->dy);

        self->dx *= PLATFORM_SPEED;
        self->dy *= PLATFORM_SPEED;
    }

    if (fabsf(self->x - self->ex) < PLATFORM_SPEED && fabsf(self->y - self->ey) < PLATFORM_SPEED) {
        calcSlope(self->sx, self->sy, self->x, self->y, &self->dx, &self->dy);

        self->dx *= PLATFORM_SPEED;
        self->dy *= PLATFORM_SPEED;
    }
}

void initPlatform(char *line) {
    struct Entity *e;

    e = malloc(sizeof(struct Entity));
    memset(e, 0, sizeof(struct Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    sscanf(line, "%*s %f %f %f %f", &e->sx, &e->sy, &e->ex, &e->ey);

    e->health = 1;

    e->x = e->sx;
    e->y = e->sy;

    e->tick = tick;

    e->texture = loadTexture("gfx/platform.png");
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->flags = EF_SOLID + EF_WEIGHTLESS + EF_PUSH;
}
