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

    SDL_Color debut = {200, 50, 50, 255};
    SDL_Color fin = {50, 50, 200, 255};
    SDL_Color check = {50, 200, 50, 255};

    SDL_Color mur = {0, 0, 0, 255};
    SDL_Color air = {255, 255, 255, 255};
    SDL_Color slime = {0, 255, 0, 255};
    SDL_Color glace = {0, 255, 255, 255};
    SDL_Color pique = {255, 0, 0, 255};
    SDL_Color plateforme = {100, 100, 100, 255};
    SDL_Color eau = {50, 50, 255, 255};

    SDL_Color colorOff = {255, 255, 255, 100};
    SDL_Color colorOn = {200, 200, 200, 200};

    // Boutons de la barre de menu
    this->butTuile =        Button((char *)"Tuile",     20, 2, 0,   100, 100, 50, transparent, gray, 2, black);
    this->butGraphique =    Button((char *)"Graphique", 20, 2, 100, 100, 100, 50, transparent, gray, 2, black);
    this->butMap =          Button((char *)"Map",       20, 2, 200, 100, 100, 50, transparent, gray, 2, black);

    // Boutons pour le choix de zone et de tuile
    this->butZoneStart =      Button((char *)" ", 10, 1, 30, 200, 60, 60, debut, debut, 2, black);
    this->butZoneEnd =        Button((char *)" ", 10, 1, 120, 200, 60, 60, fin, fin, 2, black);
    this->butZoneCheckpoint = Button((char *)" ", 10, 1, 210, 200, 60, 60, check, check, 2, black);
    this->butTuileMur =   Button((char *)" ", 10, 1, 30, 330, 60, 60, mur, mur, 2, black);
    this->butTuileAir =   Button((char *)" ", 10, 1, 120, 330, 60, 60, air, air, 2, black);
    this->butTuileSlime = Button((char *)" ", 10, 1, 210, 330, 60, 60, slime, slime, 2, black);
    this->butTuileGlace = Button((char *)" ", 10, 1, 30, 430, 60, 60, glace, glace, 2, black);
    this->butTuilePique = Button((char *)" ", 10, 1, 120, 430, 60, 60, pique, pique, 2, black);
    this->butTuilePlateforme =  Button((char *)" ", 10, 1, 210, 430, 60, 60, plateforme, plateforme, 2, black);
    this->butTuileEau =         Button((char *)" ", 10, 1, 30, 530, 60, 60, eau, eau, 2, black);

    // Boutons pour l'onglet map
    this->inputMapname = Input((char *)" ", 20, 1, 20, false, 50, 190, 200, 30, colorOff, colorOn, 2, black, black);
    this->inputMapname.setValue(this->mapName);
    this->inputMapW = Input((char *)" ", 20, 1, 3, true, 90, 270, 45, 30, colorOff, colorOn, 2, black, black);
    this->inputMapW.setValue(std::to_string(this->mapW));
    this->inputMapH = Input((char *)" ", 20, 1, 3, true, 170, 270, 45, 30, colorOff, colorOn, 2, black, black);
    this->inputMapH.setValue(std::to_string(this->mapH));
    this->butValiderInputMap = Button((char *)"Appliquer les changements", 20, 1, 25, 400, 250, 40, colorOff, colorOn, 2, black);
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
        if (this->butZoneStart.clicOnButton())
            this->choice = -1;
        else if (this->butZoneEnd.clicOnButton())
            this->choice = -2;
        else if (this->butZoneCheckpoint.clicOnButton())
            this->choice = -3;
        else if (this->butTuileMur.clicOnButton())
            this->choice = 0;
        else if (this->butTuileAir.clicOnButton())
            this->choice = 1;
        else if (this->butTuileSlime.clicOnButton())
            this->choice = 2;
        else if (this->butTuileGlace.clicOnButton())
            this->choice = 3;
        else if (this->butTuilePique.clicOnButton())
            this->choice = 4;
        else if (this->butTuilePlateforme.clicOnButton())
            this->choice = 5;
        else if (this->butTuileEau.clicOnButton())
            this->choice = 6;
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
    drawText(renderer, (char *)"Editeur", 40, 150, 20, 1, black);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
    SDL_Rect rect2 = {100 * this->fen, 100, 100, 50}; // Création du carré (x, y, width, height)
    SDL_RenderFillRect(renderer, &rect2); // Dessin du carré

    this->butTuile.draw(renderer);
    this->butGraphique.draw(renderer);
    this->butMap.draw(renderer);

    if (this->fen == 0){
        drawText(renderer, (char *)"Zones", 25, 150, 170, 1, black);
        this->butZoneStart.draw(renderer);
        drawText(renderer, (char *)"debut", 20, 60, 260, 1, black);
        this->butZoneEnd.draw(renderer);
        drawText(renderer, (char *)"fin", 20, 150, 260, 1, black);
        this->butZoneCheckpoint.draw(renderer);
        drawText(renderer, (char *)"checkpoint", 20, 240, 260, 1, black);

        drawText(renderer, (char *)"Tuiles", 25, 150, 300, 1, black);

        this->butTuileMur.draw(renderer);
        drawText(renderer, (char *)"mur", 20, 60, 390, 1, black);
        this->butTuileAir.draw(renderer);
        drawText(renderer, (char *)"air", 20, 150, 390, 1, black);
        this->butTuileSlime.draw(renderer);
        drawText(renderer, (char *)"slime", 20, 240, 390, 1, black);

        this->butTuileGlace.draw(renderer);
        drawText(renderer, (char *)"glace", 20, 60, 490, 1, black);
        this->butTuilePique.draw(renderer);
        drawText(renderer, (char *)"pique", 20, 150, 490, 1, black);
        this->butTuilePlateforme.draw(renderer);
        drawText(renderer, (char *)"plateforme", 20, 240, 490, 1, black);

        this->butTuileEau.draw(renderer);
        drawText(renderer, (char *)"eau", 20, 60, 590, 1, black);

        int x = 0;
        int y = 0;
        switch (this->choice) {
            case -1:
                x = 30;
                y = 200;
                break;

            case -2:
                x = 120;
                y = 200;
                break;

            case -3:
                x = 210;
                y = 200;
                break;

            case 0:
                x = 30;
                y = 330;
                break;

            case 1:
                x = 120;
                y = 330;
                break;

            case 2:
                x = 210;
                y = 330;
                break;

            case 3:
                x = 30;
                y = 430;
                break;

            case 4:
                x = 120;
                y = 430;
                break;

            case 5:
                x = 210;
                y = 430;
                break;

            case 6:
                x = 30;
                y = 530;
                break;

            case 7:
                x = 120;
                y = 530;
                break;
        }

        for (int i = 0; i < 2; i++){
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_Rect rect3 = {x + i, y + i, 60 - i*2, 60 - i*2}; // Création du carré (x, y, width, height)
            SDL_RenderDrawRect(renderer, &rect3); // Dessin du carré
        }
    }
    else if (this->fen == 2){
        drawText(renderer, (char *)"Nom de la carte", 20, 150, 160, 1, black);
        this->inputMapname.draw(renderer);

        drawText(renderer, (char *)"Dimension de la carte", 20, 150, 240, 1, black);
        this->inputMapW.draw(renderer);
        drawText(renderer, (char *)"X", 20, 150, 275, 1, black);
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