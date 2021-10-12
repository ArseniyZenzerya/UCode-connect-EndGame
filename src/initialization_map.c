#include "../inc/header.h"

void initializathion_map(char * adress_map, char * adress_back, char * back_for_vic, int levelNum, char *level, char *entity, char *coinLevel) {
    stage.collectFound = 0;
    stage.collectTotal = 0;

    long then;
    float remainder;

    int run = 1;

    initStage(adress_map, level, entity, coinLevel);

    then = SDL_GetTicks();

    remainder = 0;

    while (run) {
        prepareScene();

        doInput();

        app.delegate.logic();

        prepareScene();

        app.delegate.draw(adress_back);

        presentScene();
        capFrameRate(&then, &remainder);
        if (app.keyboard[SDL_SCANCODE_ESCAPE]) {
            run = 0;
            app.keyboard[SDL_SCANCODE_ESCAPE] = 0;
            SDL_Delay(200);
            switch_lvl();
        }
        if (stage.collectFound == stage.collectTotal) {
            if (levelNum == 1) {

                run = 0;
                prepareScene();
                SDL_Texture *background_vic = loadTexture(back_for_vic);
                SDL_Rect background_victory;
                background_victory.x = 0;
                background_victory.y = 0;
                background_victory.w = SCREEN_WIDTH;
                background_victory.h = SCREEN_HEIGHT;

                SDL_RenderCopy(app.renderer, background_vic, NULL, &background_victory);

                SDL_RenderPresent(app.renderer);

                prepareScene();
                SDL_Delay(4000);
                exit(1);
            } else {
                run = 0;
                prepareScene();
                SDL_Texture *background_vic = loadTexture(back_for_vic);
                SDL_Rect background_victory;
                background_victory.x = 0;
                background_victory.y = 0;
                background_victory.w = SCREEN_WIDTH;
                background_victory.h = SCREEN_HEIGHT;

                SDL_RenderCopy(app.renderer, background_vic, NULL, &background_victory);

                SDL_RenderPresent(app.renderer);

                prepareScene();
                SDL_Delay(1500);
                stage.collectFound = 0;
                stage.collectTotal = 0;
                switch_lvl();
            }
        }


        if (app.keyboard[SDL_SCANCODE_R]) {
            run = 0;
            prepareScene();
            SDL_Texture *background = loadTexture("resource/images/restart.png");
            SDL_Rect background1_st;
            background1_st.x = 0;
            background1_st.y = 0;
            background1_st.w = SCREEN_WIDTH;
            background1_st.h = SCREEN_HEIGHT;

            SDL_RenderCopy(app.renderer, background, NULL, &background1_st);

            SDL_RenderPresent(app.renderer);


            // SDL_DestroyTexture(background);

            prepareScene();
            SDL_Delay(500);


            initializathion_map(adress_map, adress_back, back_for_vic, levelNum, level, entity, coinLevel);

        }


    }

}


