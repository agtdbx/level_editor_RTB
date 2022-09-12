//
// Created by auguste on 30/07/22.
//

#ifndef EDITEUR_RTB_EDITORBAR_H
#define EDITEUR_RTB_EDITORBAR_H

#include <string>
#include "SDL.h"
#include "../include/Button.h"
#include "../include/Input.h"

class EditorBar {
private:
    int x, y, w, h, fen, choice, mapW, mapH;
    std::string mapName;
    bool mouseOver;
    Button butTuile, butGraphique, butMap,
            butZoneStart, butZoneEnd, butZoneCheckpoint,
            butTuileMur, butTuileAir, butTuileSlime, butTuileGlace, butTuilePique, butTuilePlateforme, butTuileFragile, butTuileEau,
            butValiderInputMap;
    Input inputMapname, inputMapW, inputMapH;

    void initButtons();

public:
    EditorBar();
    EditorBar(int winW, int winH, std::string mapName, int mapW, int mapH);
    ~EditorBar();

    void input(SDL_Event event);
    void tick();
    void draw(SDL_Renderer *renderer);
    int getFen();
    int getChoice();
    std::string getMapname();
    int getMapW();
    int getMapH();
};


#endif //EDITEUR_RTB_EDITORBAR_H
