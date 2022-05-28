//
// Created by auguste on 31/01/2022.
//

#include "../include/Button.h"

#include <SDL.h>
#include "../include/Functions.h"

//Private methods
void Button::mouseOnButton() {
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

//Public methods
Button::Button() {

}

Button::Button(char *text, int textSize, int textAlign, int x, int y, int width, int height, SDL_Color colorOff, SDL_Color colorOn, int borderSize, SDL_Color borderColor) {
    this->text = text;
    this->textSize = textSize;
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->colorOff = colorOff;
    this->colorOn = colorOn;
    this->textAlign = textAlign;
    this->borderSize = borderSize;
    this->borderColor = borderColor;
}


Button::~Button() {

}


void Button::draw(SDL_Renderer *renderer) {
    this->mouseOnButton();
    if (!this->mouseOver){
        SDL_SetRenderDrawColor(renderer, this->colorOff.r, this->colorOff.g, this->colorOff.b, this->colorOff.a);
    }
    else{
        SDL_SetRenderDrawColor(renderer, this->colorOn.r, this->colorOn.g, this->colorOn.b, this->colorOn.a);
    }
    SDL_Rect rect = {this->x, this->y, this->w, this->h}; // Création du carré (x, y, width, height)
    SDL_RenderFillRect(renderer, &rect); // Dessin du carré
    SDL_Color color = {0, 0, 0, 255};
    drawText(renderer, this->text, this->textSize, this->x + this->w/2, this->y, this->textAlign, color);

    SDL_SetRenderDrawColor(renderer, this->borderColor.r, this->borderColor.g, this->borderColor.b, this->borderColor.a);
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {this->x + i, this->y +i, this->w - i*2, this->h - i*2};
        SDL_RenderDrawRect(renderer, &rect);
    }
}

bool Button::clicOnButton() {
    bool rep = false;
    int x, y;
    Uint32 buttons;

    SDL_PumpEvents();

    buttons = SDL_GetMouseState(&x, &y);

    if ((buttons & SDL_BUTTON_LMASK) != 0 && this->mouseOver) {
        rep = true;
    }

    return rep;
}

void Button::setX(int x) {
    this->x = x;
}

void Button::setY(int y) {
    this->y = y;
}