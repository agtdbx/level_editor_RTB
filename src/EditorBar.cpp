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


EditorBar::EditorBar(int winW, int winH) {
    this->x = 0;
    this->y = 0;
    this->w = 300;
    this->h = winH;
    this->fen = 0;
    this->choice = 0;

    this->initButtons();
}


EditorBar::~EditorBar() {

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
        this->butTuileAir.draw(renderer);
        this->butTuileSlime.draw(renderer);
        this->butTuileGlace.draw(renderer);
        this->butTuilePique.draw(renderer);

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
}


int EditorBar::getFen() {
    return this->fen;
}


int EditorBar::getChoice() {
    return this->choice;
}