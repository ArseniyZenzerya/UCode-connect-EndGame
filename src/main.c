#include "../inc/header.h"

int main() {
    memset(&app, 0, sizeof(App));
    app.textureTail = &app.textureHead;

    initSDL();

    if (menu(app.renderer) == 1) {

        atexit(cleanup);

        switch_lvl();
    } else if (menu(app.renderer) == 2) {
        atexit(cleanup);

        howToPlay();
    }

    return 0;
}
