//
// Created by auguste on 30/05/22.
//

#include "../include/Input.h"

#include <SDL.h>
#include "../include/Functions.h"

// Fonctions
char* appendCharToCharArray(char* array, char a)
{
    size_t len = strlen(array);

    char* ret = new char[len+2];

    strcpy(ret, array);
    ret[len] = a;
    ret[len+1] = '\0';

    return ret;
}


//Private methods
void Input::mouseOnButton() {
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


void Input::clicOnButton() {
    int x, y;
    Uint32 buttons;

    SDL_PumpEvents();

    buttons = SDL_GetMouseState(&x, &y);

    if ((buttons & SDL_BUTTON_LMASK) != 0 && SDL_GetTicks()/1000 - this->lastClick > 0.3) {
        this->lastClick = SDL_GetTicks()/1000;
        if (this->mouseOver){
            this->write = !this->write;
        }
        else{
            this->write = false;
        }
    }
}


//Public methods
Input::Input() {

}


Input::Input(char *text, int textSize, int textAlign, int maxLength, bool intOnly, int x, int y, int w, int h, SDL_Color colorOff, SDL_Color colorOn, int borderSize, SDL_Color borderColor, SDL_Color writeColor) {
    this->text = text;
    this->textSize = textSize;
    this->textAlign = textAlign;
    this->maxLength = maxLength;
    this->intOnly = intOnly;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->value = "";
    this->colorOff = colorOff;
    this->colorOn = colorOn;
    this->borderSize = borderSize;
    this->borderColor = borderColor;
    this->writeColor = writeColor;
    this->write = false;
    this->shift = false;
}


Input::~Input() {

}


void Input::draw(SDL_Renderer *renderer) {
    this->mouseOnButton();
    this->clicOnButton();
    if (!this->mouseOver){
        SDL_SetRenderDrawColor(renderer, this->colorOff.r, this->colorOff.g, this->colorOff.b, this->colorOff.a);
    }
    else{
        SDL_SetRenderDrawColor(renderer, this->colorOn.r, this->colorOn.g, this->colorOn.b, this->colorOn.a);
    }
    SDL_Rect rect = {this->x, this->y, this->w, this->h}; // Création du carré (x, y, width, height)
    SDL_RenderFillRect(renderer, &rect); // Dessin du carré

    if (this->value == ""){
        SDL_Color color = {100, 100, 100, 200};
        drawText(renderer, this->text, this->textSize, this->x + this->w/2, this->y, this->textAlign, color);
    }
    else{
        SDL_Color color = {0, 0, 0, 255};
        char* text = const_cast<char*>(this->value.c_str());
        drawText(renderer, text, this->textSize, this->x + this->w/2, this->y, this->textAlign, color);
    }

    if (this->write){
        SDL_SetRenderDrawColor(renderer, 100, 100, 255, this->borderColor.a);
    }
    else{
        SDL_SetRenderDrawColor(renderer, this->borderColor.r, this->borderColor.g, this->borderColor.b, this->borderColor.a);
    }
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {this->x + i, this->y +i, this->w - i*2, this->h - i*2};
        SDL_RenderDrawRect(renderer, &rect);
    }
}


void Input::giveInput(int input) {
    if (input == 127){
        this->value = "";
    }
    else if (input == 8){
        if (this->value != ""){
            this->value.pop_back();
        }
    }
    else if(this->value.length() < maxLength){
        if (input == 32 && !this->intOnly){
            this->value.push_back(' ');
        }
        else if (input >= 48 && input <= 57){
            char c = input;
            if (!this->shift && !this->intOnly){
                if (input == 49){
                    c = '&';
                }
                else if (input == 54){
                    c = '-';
                }
                else if (input == 56){
                    c = '_';
                }
                else{
                    return;
                }

            }
            this->value.push_back(c);
        }
        else if (input >= 97 && input <= 122 && !this->intOnly){
            char c = input;
            if (this->shift){
                c = toupper(c);
            }
            this->value.push_back(c);
        }
    }
}


void Input::setX(int x) {
    this->x = x;
}

void Input::setY(int y) {
    this->y = y;
}

void Input::setShift(bool state) {
    this->shift = state;
}

void Input::setValue(std::string value) {
    this->value = value;
}

char *Input::getValue() {
    return const_cast<char*>(this->value.c_str());
}

bool Input::getWrite() {
    return this->write;
}

bool Input::isEmpty() {
    return this->value == "";
}