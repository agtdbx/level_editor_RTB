//
// Created by auguste on 01/02/2022.
//

#include "../include/Select.h"
#include <SDL2/SDL.h>
#include "../include/Functions.h"

//Private methods
void Select::mouseOnButton() {
    int x, y;
    Uint32 buttons;

    SDL_PumpEvents();  // make sure we have the latest mouse state.

    buttons = SDL_GetMouseState(&x, &y);

    if (!this->extend){
        if ((x >= this->x && x <= this->x + this->w) && (y >= this->y && y <= this->y + this->h)){
            this->mouseOver = 0;
        }
        else{
            this->mouseOver = -1;
        }
    }
    else{
        if ((x >= this->x && x <= this->x + this->w) && (y >= this->y && y <= this->y + this->h*(this->values.size()+1))){
            this->mouseOver = (y - this->y)/this->h;
        }
        else{
            this->mouseOver = -1;
        }
    }
}


bool Select::clicOnButton() {
    bool res = false;
    int x, y;
    Uint32 buttons;

    SDL_PumpEvents();

    buttons = SDL_GetMouseState(&x, &y);

    if ((buttons & SDL_BUTTON_LMASK) != 0 && this->mouseOver > -1) {
        if (!this->extend){
            this->extend = true;
        }
        else{
            if (this->mouseOver > 0) {
                this->text = this->values[this->mouseOver - 1];
                this->extend = false;
                res = true;
            }
        }
    }
    else if ((buttons & SDL_BUTTON_LMASK) != 0 && this->mouseOver != 0){
        this->extend = false;
    }

    return res;
}


//Public methods
Select::Select() {

}

Select::Select(char *text, int textSize, int textAlign, int x, int y, int width, int height, SDL_Color colorOff, SDL_Color colorOn, std::vector<char*> values, int borderSize, SDL_Color borderColor) {
    this->text = text;
    this->textSize = textSize;
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    this->colorOff = colorOff;
    this->colorOn = colorOn;
    this->textAlign = textAlign;
    this->extend = false;
    this->values = values;
    this->borderSize = borderSize;
    this->borderColor = borderColor;
}


Select::~Select() {

}


bool Select::draw(SDL_Renderer *renderer) {
    this->mouseOnButton();
    bool res = this->clicOnButton();
    if (this->mouseOver == 0){
        SDL_SetRenderDrawColor(renderer, this->colorOn.r, this->colorOn.g, this->colorOn.b, this->colorOn.a);
    }
    else{
        SDL_SetRenderDrawColor(renderer, this->colorOff.r, this->colorOff.g, this->colorOff.b, this->colorOff.a);
    }

    SDL_Rect rect = {this->x, this->y, this->w, this->h}; // Création du carré (x, y, width, height)
    SDL_RenderFillRect(renderer, &rect); // Dessin du carré
    SDL_Color color = {0, 0, 0, 255};
    drawText(renderer, this->text, this->textSize, this->x + this->w/2, this->y, this->textAlign, color);

    SDL_SetRenderDrawColor(renderer, this->borderColor.r, this->borderColor.g, this->borderColor.b, this->borderColor.a);
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {this->x + i, this->y +i, this->w - i*2, this->h - i*2}; // Création du carré (x, y, width, height)
        SDL_RenderDrawRect(renderer, &rect); // Dessin du carré
    }

    if (this->extend){
        SDL_SetRenderDrawColor(renderer, this->borderColor.r, this->borderColor.g, this->borderColor.b, this->borderColor.a);
        for (int i = 0; i < this->borderSize; ++i){
            SDL_Rect rect = {this->x + i, this->y +i, this->w - i*2, this->h * (int)(this->values.size()+1) - i*2}; // Création du carré (x, y, width, height)
            SDL_RenderDrawRect(renderer, &rect); // Dessin du carré
        }
        for (int i = 0; i < this->values.size(); ++i){
            if (this->mouseOver == i+1){
                SDL_SetRenderDrawColor(renderer, this->colorOn.r, this->colorOn.g, this->colorOn.b, this->colorOn.a);
            }
            else{
                SDL_SetRenderDrawColor(renderer, this->colorOff.r, this->colorOff.g, this->colorOff.b, this->colorOff.a);
            }
            SDL_Rect rect = {this->x, this->y + (i+1)*40, this->w, this->h};
            SDL_RenderFillRect(renderer, &rect);
            drawText(renderer, this->values[i], this->textSize, this->x + this->w/2, this->y + (i+1)*40, this->textAlign, color);
        }
    }

    return res;
}


char* Select::getValue() {
    return this->text;
}

void Select::setX(int x) {
    this->x = x;
}

void Select::setValue(std::string value) {
    for (int i = 0; i < this->values.size(); ++i){
        if (value == this->values[i]){
            this->text = this->values[i];
            break;
        }
    }
}