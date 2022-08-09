//
// Created by auguste on 31/05/22.
//

#ifndef EDITEUR_RTB_MAP_H
#define EDITEUR_RTB_MAP_H

#include <iostream>
#include <vector>
#include "../include/Tuile.h"
#include "../include/Checkpoint.h"
#include <SDL_image.h>

class Map {
private:
    std::vector<Checkpoint> checkpoints;
    std::vector<std::vector<Tuile>> map;
    int w, h, startX, startY, endX, endY, squareSize;

    void initEmptyMap();
    std::vector<std::vector<Tuile>> copyMap();

public:
    Map();
    Map(int w, int h, int squareSize);
    ~Map();

    void draw(SDL_Renderer *renderer, Camera camera, int winW, int winH);
    Tuile get(int x, int y);
    bool test(int x, int y);
    int getSquarreSize();
    int getStartX();
    int getStartY();
    int getEndX();
    int getEndY();
    int getWidth();
    int getHeigth();
    std::vector<Checkpoint> getCheckpoint();
    Checkpoint testCheckpoint(float x, float y, int w, int h);
    void set(int x, int y, Tuile t);
    void addCheckpoint(Checkpoint checkpoint);
    void resize(int mapW, int mapH);
};


#endif //EDITEUR_RTB_MAP_H
