//
// Created by auguste on 31/05/22.
//

#include "../include/Map.h"
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Tuile.h"
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <SDL2/SDL_image.h>

//private methods
void Map::initEmptyMap() {
    this->map.clear();

    for (int i = 0; i < this->w; ++i){
        std::vector<Tuile> vector;
        for (int j = 0; j < this->h; ++j){
            Tuile tuile;
            if (i == 0 || i == this->w-1 || j == 0 || j == this->h-1){
                tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, "mur");
            }
            else{
                tuile = Tuile(i*this->squareSize, j*this->squareSize, this->squareSize, "air");
            }
            vector.push_back(tuile);
        }
        this->map.push_back(vector);
    }
}


std::vector<std::vector<Tuile>> Map::copyMap() {
    std::vector<std::vector<Tuile>> copyMap;

    for (int x = 0; x < this->map.size(); x++){
        std::vector<Tuile> vector;
        for (int y = 0; y < this->map[0].size(); y++){
            vector.push_back(this->map[x][y]);
        }
        copyMap.push_back(vector);
    }

    return copyMap;
}


//public methods
Map::Map() {
    this->w = 32;
    this->h = 18;
    this->start = Zone(1, 1, "start");
    this->end = Zone(3, 3, "end");
    this->squareSize = 20;

    initEmptyMap();
}

Map::Map(int w, int h, int squareSize) {
    this->w = w;
    this->h = h;
    this->start = Zone(1, 1, "start");
    this->end = Zone(3, 3, "end");
    this->squareSize = squareSize;

    initEmptyMap();
}


Map::~Map() {

}


void Map::draw(SDL_Renderer *renderer, Camera camera, int winW, int winH) {
    int minX = 280;
    int minY = -20;
    for (int i = 0; i < this->w; ++i) {
        for (int j = 0; j < this->h; ++j) {
            if (minX <= i*20 - camera.getX() && i*20 - camera.getX() <= winW && minY <= j*20 - camera.getY() && j*20 - camera.getY() <= winH){
                this->map[i][j].draw(renderer, camera);
            }
        }
    }

    this->start.draw(renderer, camera);
    this->end.draw(renderer, camera);
}


Tuile Map::get(int x, int y) {
    return this->map[x][y];
}


bool Map::test(int x, int y) {
    return this->map[x][y].isPassable();
}


int Map::getSquarreSize() {
    return this->squareSize;
}


void Map::setStart(Zone start) {
    this->start = start;
}


Zone Map::getStart() {
    return this->start;
}


void Map::setEnd(Zone end) {
    this->end = end;
}


Zone Map::getEnd() {
    return this->end;
}


Zone Map::testCheckpoint(float x, float y, int w, int h) {
    Zone rep = Zone(0, 0, -1);

    for (Zone checkpoint : this->checkpoints){
        if (checkpoint.getX() <= (x + w) && (checkpoint.getX() + 3*20) >= x && checkpoint.getY() <= (y + h) && (checkpoint.getY() + 3*20) >= y){
            rep = checkpoint;
        }
    }

    return rep;
}


int Map::getWidth() {
    return this->w;
}


int Map::getHeigth() {
    return this->h;
}


std::vector<Zone> Map::getCheckpoint() {
    return this->checkpoints;
}


void Map::set(int x, int y, Tuile t) {
    this->map[x][y] = t;
}


void Map::addCheckpoint(Zone checkpoint) {
    this->checkpoints.push_back(checkpoint);
}


void Map::resize(int mapW, int mapH) {
    std::cout << "RESIZE : " << this->w << "x" << this->h << " en " << mapW << "x" << mapH << std::endl;
    std::vector<std::vector<Tuile>> copyMap = this->copyMap();

    this->w = mapW;
    this->h = mapH;
    this->initEmptyMap();

    for (int x = 1; x < this->map.size()-1; x++){
        for (int y = 1; y < this->map[0].size()-1; y++){
            if (x < copyMap.size()-1 && y < copyMap[0].size()-1){
                this->map[x][y] = copyMap[x][y];
            }
        }
    }
}