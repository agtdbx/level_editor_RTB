//
// Created by auguste on 30/07/22.
//

#include "../include/EditorBar.h"
#include "../include/Functions.h"

// Private methods
void EditorBar::initButtons() {
    // Définition des couleurs
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color transparent = {0, 0, 0, 0};
    SDL_Color gray= {150, 150, 150, 150};
    SDL_Color mur = {0, 0, 0, 255};
    SDL_Color air = {255, 255, 255, 255};
    SDL_Color slime = {0, 255, 0, 255};
    SDL_Color glace = {0, 255, 255, 255};
    SDL_Color pique = {100, 100, 100, 255};

    SDL_Color colorOff = {255, 255, 255, 100};
    SDL_Color colorOn = {200, 200, 200, 200};

    // Boutons de la barre de menu
    this->butTuile =        Button("Tuile",     20, 2, 0,   100, 100, 50, transparent, gray, 2, black);
    this->butGraphique =    Button("Graphique", 20, 2, 100, 100, 100, 50, transparent, gray, 2, black);
    this->butMap =          Button("Map",       20, 2, 200, 100, 100, 50, transparent, gray, 2, black);

    // Boutons pour le choix de tuile
    this->butTuileMur =   Button(" ", 10, 1, 60, 200, 60, 60, mur, mur, 2, black);
    this->butTuileAir =   Button(" ", 10, 1, 180, 200, 60, 60, air, air, 2, black);
    this->butTuileSlime = Button(" ", 10, 1, 60, 320, 60, 60, slime, slime, 2, black);
    this->butTuileGlace = Button(" ", 10, 1, 180, 320, 60, 60, glace, glace, 2, black);
    this->butTuilePique = Button(" ", 10, 1, 60, 440, 60, 60, pique, pique, 2, black);

    // Boutons pour l'onglet map
    this->inputMapname = Input(" ", 20, 1, 20, false, 50, 190, 200, 30, colorOff, colorOn, 2, black, black);
    this->inputMapname.setValue(this->mapName);
    this->inputMapW = Input(" ", 20, 1, 3, true, 90, 270, 45, 30, colorOff, colorOn, 2, black, black);
    this->inputMapW.setValue(std::to_string(this->mapW));
    this->inputMapH = Input(" ", 20, 1, 3, true, 170, 270, 45, 30, colorOff, colorOn, 2, black, black);
    this->inputMapH.setValue(std::to_string(this->mapH));
    this->butValiderInputMap = Button("Appliquer les changements", 20, 1, 25, 400, 250, 40, colorOff, colorOn, 2, black);
}



// Public methods
EditorBar::EditorBar() {
    this->x = 0;
    this->y = 0;
    this->w = 10;
    this->h = 10;
    this->fen = 0;
    this->choice = 0;
}


EditorBar::EditorBar(int winW, int winH, std::string mapName,int mapW, int mapH) {
    this->x = 0;
    this->y = 0;
    this->w = 300;
    this->h = winH;
    this->fen = 0;
    this->choice = 0;
    this->mapName = mapName;
    this->mapW = mapW;
    this->mapH = mapH;

    this->initButtons();
}


EditorBar::~EditorBar() {

}


void EditorBar::input(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_LSHIFT){
                this->inputMapname.setShift(true);
                this->inputMapW.setShift(true);
                this->inputMapH.setShift(true);
            }
            if (this->fen == 2){
                if (this->inputMapname.getWrite()){
                    this->inputMapname.giveInput(event.key.keysym.sym);
                }
                else if (this->inputMapW.getWrite()){
                    this->inputMapW.giveInput(event.key.keysym.sym);
                }
                else if (this->inputMapH.getWrite()){
                    this->inputMapH.giveInput(event.key.keysym.sym);
                }
            }
            break;

        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_LSHIFT){
                this->inputMapname.setShift(false);
                this->inputMapW.setShift(false);
                this->inputMapH.setShift(false);
            }
            break;
    }
}


void EditorBar::tick() {
    if (this->butTuile.clicOnButton()){
        this->fen = 0;
        this->choice = 0;
    }
    else if (this->butGraphique.clicOnButton()){
        this->fen = 1;
        this->choice = 0;
    }
    else if (this->butMap.clicOnButton()){
        this->fen = 2;
        this->choice = 0;
    }

    if (this->fen == 0){
        if (this->butTuileMur.clicOnButton()){
            this->choice = 0;
        }
        if (this->butTuileAir.clicOnButton()){
            this->choice = 1;
        }
        if (this->butTuileSlime.clicOnButton()){
            this->choice = 2;
        }
        if (this->butTuileGlace.clicOnButton()){
            this->choice = 3;
        }
        if (this->butTuilePique.clicOnButton()){
            this->choice = 4;
        }
    }
    else if (this->fen == 2){
        if (this->inputMapname.getValue() != this->mapName || atoi(this->inputMapW.getValue()) != this->mapW || atoi(this->inputMapH.getValue()) != this->mapH){
            if (this->butValiderInputMap.clicOnButton()){
                this->mapName = this->inputMapname.getValue();
                this->mapW = atoi(this->inputMapW.getValue());
                this->mapH = atoi(this->inputMapH.getValue());
            }
        }
    }
}


void EditorBar::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_Rect rect = {this->x, this->y, this->w, this->h}; // Création du carré (x, y, width, height)
    SDL_RenderFillRect(renderer, &rect); // Dessin du carré

    SDL_Color black = {0, 0, 0, 255};
    drawText(renderer, "Editeur", 40, 150, 20, 1, black);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
    SDL_Rect rect2 = {100 * this->fen, 100, 100, 50}; // Création du carré (x, y, width, height)
    SDL_RenderFillRect(renderer, &rect2); // Dessin du carré

    this->butTuile.draw(renderer);
    this->butGraphique.draw(renderer);
    this->butMap.draw(renderer);

    if (this->fen == 0){
        this->butTuileMur.draw(renderer);
        drawText(renderer, "mur", 20, 90, 260, 1, black);
        this->butTuileAir.draw(renderer);
        drawText(renderer, "air", 20, 210, 260, 1, black);
        this->butTuileSlime.draw(renderer);
        drawText(renderer, "slime", 20, 90, 380, 1, black);
        this->butTuileGlace.draw(renderer);
        drawText(renderer, "glace", 20, 210, 380, 1, black);
        this->butTuilePique.draw(renderer);
        drawText(renderer, "pique", 20, 90, 500, 1, black);

        int x = 0;
        int y = 0;
        switch (this->choice) {
            case 0:
                x = 60;
                y = 200;
                break;

            case 1:
                x = 180;
                y = 200;
                break;

            case 2:
                x = 60;
                y = 320;
                break;

            case 3:
                x = 180;
                y = 320;
                break;

            case 4:
                x = 60;
                y = 440;
                break;
        }

        for (int i = 0; i < 2; i++){
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_Rect rect3 = {x + i, y + i, 60 - i*2, 60 - i*2}; // Création du carré (x, y, width, height)
            SDL_RenderDrawRect(renderer, &rect3); // Dessin du carré
        }
    }
    else if (this->fen == 2){
        drawText(renderer, "Nom de la carte", 20, 150, 160, 1, black);
        this->inputMapname.draw(renderer);

        drawText(renderer, "Dimension de la carte", 20, 150, 240, 1, black);
        this->inputMapW.draw(renderer);
        drawText(renderer, "X", 20, 150, 275, 1, black);
        this->inputMapH.draw(renderer);

        if (this->inputMapname.getValue() != this->mapName || atoi(this->inputMapW.getValue()) != this->mapW || atoi(this->inputMapH.getValue()) != this->mapH){
            this->butValiderInputMap.draw(renderer);
        }
    }
}


int EditorBar::getFen() {
    return this->fen;
}


int EditorBar::getChoice() {
    return this->choice;
}


std::string EditorBar::getMapname() {
    return this->mapName;
}


int EditorBar::getMapW() {
    return this->mapW;
}


int EditorBar::getMapH() {
    return this->mapH;
}