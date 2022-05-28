//
// Created by auguste on 28/05/2022.
//

#ifndef RTB_MENU_H
#define RTB_MENU_H

#include <SDL.h>
#include "../include/Button.h"
#include "../include/Select.h"
#include "../include/Switch.h"

class Menu {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winW, winH, fenetre, spacingWithScreen, borderSize;
    float lastClic, lastTime;
    bool run, continuer;
    Button butJouer, butOptions, butQuitter,
            butRetourJouer,
            butGraphics,
            butCredit,
            butRetourOptions;
    Select butChoixRes;
    Switch fullScreen;

    void initButton();
    void input();
    void tick();
    void render();
    void drawBaseOptions();
    void drawGraphicOptions();
    void drawSoundsOptions();
    void drawKeyboardOptions();
    void drawCredit();
    void setScreenSize();
    void setScreenMode();
    char * drawKeyBind(int key);
    void saveOptions();
    void loadOptions();

public:
    Menu(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH);
    ~Menu();

    bool start();
    int getNumLevel();
    int getVolumeSon();
    int getVolumeMusique();
    int getToucheGauche();
    int getToucheDroite();
    int getToucheSaut();
    int getWinWidth();
    int getWinHeight();
};


#endif //RTB_MENU_H
