#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "../include/Menu.h"
#include "../include/Editor.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    int winW = 1920;
    int winH = 1080;

    SDL_Window *window = SDL_CreateWindow("RTB",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH,
                                          SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Menu menu = Menu(window, renderer, winW, winH);
    Editor editor = Editor(renderer, winW, winH);

    bool run = true;

    while (run){
        if (menu.start()){
            editor.setVariables(menu.getWinWidth(), menu.getWinHeight(), menu.getMap(), menu.getMapname(), menu.getFilename());
            editor.start();
        }
        else{
            run = false;
        }
    }

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
