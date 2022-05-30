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
    int x, y, w, h, textSize, textAlign, borderSize;
    float lastClick;
    bool write, mouseOver;
    std::string value;
    char* text;
    SDL_Color colorOff, colorOn, borderColor;

    void mouseOnButton();
    void clicOnButton();

public:
    Input();
    Input(char* text, int textSize, int textAlign, int x, int y, int w, int h, SDL_Color colorOff, SDL_Color colorOn, int borderSize, SDL_Color borderColor);
    ~Input();

    void draw(SDL_Renderer *renderer);
    void giveInput(int input);
    void setX(int x);
    void setY(int y);
    char* getValue();
    bool getWrite();
};


#endif //EDITEUR_RTB_INPUT_H
