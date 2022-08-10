//
// Created by auguste on 09/08/22.
//

#ifndef EDITEUR_RTB_ZONE_H
#define EDITEUR_RTB_ZONE_H


#include <string>
#include "SDL.h"
#include "../include/Camera.h"

class Zone {
private:
    int x, y, w, h, id;
    SDL_Color color;

public:
    Zone();
    Zone(int x, int y, std::string type);
    Zone(int x, int y, int id);
    ~Zone();

    void draw(SDL_Renderer *renderer, Camera camera);
    bool inZone(int x, int y);
    int getX();
    int getY();
    int getId();
    void setId(int id);
};


#endif //EDITEUR_RTB_ZONE_H
