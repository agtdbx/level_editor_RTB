//
// Created by auguste on 02/02/2022.
//

#ifndef RTB_SWITCH_H
#define RTB_SWITCH_H

#include <SDL.h>

class Switch {
private:
    int x, y, w, h, borderSize;
    float lastClic;
    bool active, mouseOver;
    SDL_Color colorOff, colorOn, borderColor;
    void mouseOnButton();
    bool clicOnButton();

public:
    Switch();
    Switch(int x, int y, int w, int h, SDL_Color colorOff, SDL_Color colorOn, int borderSize, SDL_Color borderColor);
    ~Switch();
    bool draw(SDL_Renderer *renderer);
    bool isActive();
    void setX(int x);
    void setActive(bool value);
};


#endif //RTB_SWITCH_H
