//
// Created by auguste on 30/05/22.
//

#ifndef EDITEUR_RTB_INPUT_H
#define EDITEUR_RTB_INPUT_H

#include <iostream>
#include <string>
#include "SDL.h";

class Input {
private:
    int x, y, w, h, textSize, textAlign, borderSize, maxLength;
    float lastClick;
    bool write, mouseOver, shift, intOnly;
    std::string value;
    char* text;
    SDL_Color colorOff, colorOn, borderColor, writeColor;

    void mouseOnButton();
    void clicOnButton();

public:
    Input();
    Input(char* text, int textSize, int textAlign, int maxLength, bool intOnly, int x, int y, int w, int h, SDL_Color colorOff, SDL_Color colorOn, int borderSize, SDL_Color borderColor, SDL_Color writeColor);
    ~Input();

    void draw(SDL_Renderer *renderer);
    void giveInput(int input);
    void setX(int x);
    void setY(int y);
    void setShift(bool state);
    char* getValue();
    bool getWrite();
};


#endif //EDITEUR_RTB_INPUT_H
