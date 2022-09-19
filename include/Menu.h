//
// Created by auguste on 28/05/2022.
//

#ifndef RTB_MENU_H
#define RTB_MENU_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

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
    std::string mapname, filename;
    Button butCreer, butCharger, butOptions, butQuitter,
            butValiderCreer, butRetourCreer,
            butValiderCharger, butRetourCharger,
            butGraphics,
            butCredit,
            butRetourOptions;
    Select butChoixRes;
    Switch fullScreen;
    Input inputNewName, inputNewW, inputNewH, inputLoadName;
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
    bool loadMap();

public:
    Menu(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH);
    ~Menu();

    bool start();
    int getWinWidth();
    int getWinHeight();
    Map getMap();
    std::string getMapname();
    std::string getFilename();
};


#endif //RTB_MENU_H
