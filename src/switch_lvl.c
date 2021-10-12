#include "../inc/header.h"

void switch_lvl() {
    switch (menu_level(app.renderer)) {
        case 1:
            stage.collectFound = 0;
            stage.collectTotal = 0;
            initGame("level1", "resource/level1/sound/mainTheme.mp3");
            char *adress_map1 = "resource/data/map01.dat";
            char *adress_back1 = "resource/images/first_lvl_back.png";
            char *victory1 = "resource/images/VICTORY2.png";
            initializathion_map(adress_map1, adress_back1, victory1, 0, "level1", "resource/data/ents01.dat", "level1");
            break;
        case 2:
            stage.collectFound = 0;
            stage.collectTotal = 0;
            initGame("level2", "resource/level2/sound/mainTheme.mp3");
            char *adress_map2 = "resource/data/map02.dat";
            char *adress_back2 = "resource/images/second_lvl_back.png";
            char *victory2 = "resource/images/VICTORY.png";
            initializathion_map(adress_map2, adress_back2, victory2, 0, "level2", "resource/data/ents02.dat", "level2");
            break;
        case 3:
            stage.collectFound = 0;
            stage.collectTotal = 0;
            initGame("level3", "resource/level3/sound/mainTheme.mp3");
            char *adress_map3 = "resource/data/map03.dat";
            char *adress_back3 = "resource/images/first_lvl_back.png";
            char *victory3 = "resource/images/GAME END.png";

            initializathion_map(adress_map3, adress_back3, victory3, 1, "level3", "resource/data/ents03.dat", "level3");

            break;
        default:
            break;
    }
}

