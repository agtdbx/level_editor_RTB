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
    std::string mapname, filename;
    Map map;
    Camera camera;

    void initButton();
    void input();
    void tick();
    void render();
    void saveMap();

public:
    Editor(SDL_Renderer *renderer, int winW, int winH);
    ~Editor();

    void start();
    void setVariables(int winWidth, int winHeight, Map map, std::string name, std::string filename);
};


#endif //EDITEUR_RTB_EDITOR_H
