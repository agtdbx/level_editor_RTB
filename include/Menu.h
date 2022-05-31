//
// Created by auguste on 28/05/2022.
//

#ifndef RTB_MENU_H
#define RTB_MENU_H

#include <SDL.h>
#include "../include/Button.h"
#include "../include/Select.h"
#include "../include/Switch.h"
#include "../include/Input.h"
#include "../include/Map.h"

class Menu {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winW, winH, fenetre, spacingWithScreen, borderSize;
    float lastClic, lastTime;
    bool run, continuer;
    char* mapname;
    char* filename;
    Button butCreer, butCharger, butOptions, butQuitter,
            butValiderCreer,
            butRetourCreer,
            butRetourCharger,
            butGraphics,
            butCredit,
            butRetourOptions;
    Select butChoixRes;
    Switch fullScreen;
    Input inputNewName, inputNewW, inputNewH;
    Map map;

    void initButton();
    void input();
    void tick();
    void render();
    void drawBaseOptions();
    void drawGraphicOptions();
    void drawCredit();
    void setScreenSize();
    void setScreenMode();
    void saveOptions();
    void loadOptions();

public:
    Menu(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH);
    ~Menu();

    bool start();
    int getWinWidth();
    int getWinHeight();
    Map getMap();
    char* getMapname();
    char* getFilename();
};


#endif //RTB_MENU_H
