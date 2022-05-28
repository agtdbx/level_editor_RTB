//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_BUTTON_H
#define RTB_BUTTON_H

#include <SDL.h>

class Button {
private:
    int x, y, w, h, textSize, textAlign, borderSize;
    char *text;
    bool mouseOver;
    SDL_Color colorOff, colorOn, borderColor;

    void mouseOnButton();

public:
    Button();
    Button(char *text, int textSize, int textAlign, int x, int y, int width, int height, SDL_Color colorOff, SDL_Color colorOn, int borderSize, SDL_Color borderColor);
    ~Button();

    void draw(SDL_Renderer *renderer);
    bool clicOnButton();
    void setX(int x);
    void setY(int y);
};


#endif //RTB_BUTTON_H
