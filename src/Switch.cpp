//
// Created by auguste on 02/02/2022.
//

#include "../include/Switch.h"
#include <SDL2/SDL.h>
#include "../include/Functions.h"


//Private methods
void Switch::mouseOnButton() {
    int x, y;
    Uint32 buttons;

    SDL_PumpEvents();  // make sure we have the latest mouse state.

    buttons = SDL_GetMouseState(&x, &y);

    if ((x >= this->x && x <= this->x + this->w) && (y >= this->y && y <= this->y + this->h)){
        this->mouseOver = true;
    }
    else{
        this->mouseOver = false;
    }
}


bool Switch::clicOnButton() {
    bool res = false;
    this->mouseOnButton();
    int x, y;
    Uint32 buttons;

    SDL_PumpEvents();

    buttons = SDL_GetMouseState(&x, &y);

    if ((buttons & SDL_BUTTON_LMASK) != 0 && this->mouseOver && (SDL_GetTicks()/1000)-this->lastClic > 0.1) {
        this->active = !this->active;
        this->lastClic = SDL_GetTicks()/1000;
        res = true;
    }

    return res;
}


//Public methods
Switch::Switch() {

}


Switch::Switch(int x, int y, int w, int h, SDL_Color colorOff, SDL_Color colorOn, int borderSize, SDL_Color borderColor) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->colorOff = colorOff;
    this->colorOn = colorOn;
    this->borderSize = borderSize;
    this->borderColor = borderColor;
    this->active = true;
    this->lastClic = 0.0;
}


Switch::~Switch() {

}


bool Switch::draw(SDL_Renderer *renderer) {
    bool res = this->clicOnButton();
    int rayon = (this->h - this->borderSize*2)/2;
    int xCercle = 0;
    if (!this->active){
        SDL_SetRenderDrawColor(renderer, this->colorOff.r, this->colorOff.g, this->colorOff.b, this->colorOff.a);
        xCercle = rayon + this->borderSize;
    }
    else{
        SDL_SetRenderDrawColor(renderer, this->colorOn.r, this->colorOn.g, this->colorOn.b, this->colorOn.a);
        xCercle = this->w - rayon - this->borderSize;
    }
    SDL_Rect rect = {this->x, this->y, this->w, this->h};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < this->borderSize; ++i){
        drawCircle(renderer, this->x+xCercle, this->y+rayon+this->borderSize, rayon-i);
    }

    SDL_SetRenderDrawColor(renderer, this->borderColor.r, this->borderColor.g, this->borderColor.b, this->borderColor.a);
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {this->x + i, this->y +i, this->w - i*2, this->h - i*2};
        SDL_RenderDrawRect(renderer, &rect);
    }

    return res;
}


bool Switch::isActive() {
    return this->active;
}

void Switch::setX(int x) {
    this->x = x;
}

void Switch::setActive(bool value) {
    this->active = value;
}