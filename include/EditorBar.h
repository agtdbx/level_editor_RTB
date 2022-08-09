//
// Created by auguste on 30/07/22.
//

#ifndef EDITEUR_RTB_EDITORBAR_H
#define EDITEUR_RTB_EDITORBAR_H

#include <string>
#include "SDL.h";
#include "../include/Button.h"

class EditorBar {
private:
    int x, y, w, h, fen, choice, mapW, mapH;
    std::string mapName;
    bool mouseOver;
    Button butTuile, butGraphique, butMap,
            butTuileMur, butTuileAir, butTuileSlime, butTuileGlace, butTuilePique;

    void initButtons();

public:
    EditorBar();
    EditorBar(int winW, int winH, std::string mapName,int mapW, int mapH);
    ~EditorBar();

    void tick();
    void draw(SDL_Renderer *renderer);
    int getFen();
    int getChoice();
};


#endif //EDITEUR_RTB_EDITORBAR_H
