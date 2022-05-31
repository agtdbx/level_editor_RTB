//
// Created by auguste on 31/05/22.
//

#ifndef EDITEUR_RTB_EDITOR_H
#define EDITEUR_RTB_EDITOR_H

#include <SDL.h>
#include "../include/Button.h"
#include "../include/Map.h"
#include "../include/Camera.h"

class Editor {
private:
    SDL_Renderer *renderer;
    int winW, winH, fenetre;
    bool run;
    Button butContinuer, butQuitter, butRetourMenu;
    float lastTime;
    char* mapname;
    char* filename;
    Map map;
    Camera camera;

    void initButton();
    void input();
    void tick();
    void render();

public:
    Editor(SDL_Renderer *renderer, int winW, int winH);
    ~Editor();

    void start();
    void setVariables(int winWidth, int winHeight, Map map, char* name, char* filename);
};


#endif //EDITEUR_RTB_EDITOR_H
