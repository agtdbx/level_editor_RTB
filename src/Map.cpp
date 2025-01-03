//
// Created by auguste on 31/05/22.
//

#include "../include/Map.h"
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Tuile.h"
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <SDL_image.h>

//private methods
void Map::initEmptyMap() {
    this->map.clear();

    for (int i = 0; i < this->w; ++i){
        std::vector<Tuile> vector;
        for (int j = 0; j < this->h; ++j){
            Tuile tuile;
            if (i == 0 || i == this->w-1 || j == 0 || j == this->h-1){
                tuile = Tuile(i, j, this->squareSize, "mur");
            }
            else{
                tuile = Tuile(i, j, this->squareSize, "air");
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
    this->w = 80;
    this->h = 45;
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
            if (minX <= i*this->squareSize - camera.getX() && i*this->squareSize - camera.getX() <= winW && minY <= j*this->squareSize - camera.getY() && j*this->squareSize - camera.getY() <= winH){
                this->map[i][j].draw(renderer, camera);
            }
        }
    }

    this->start.draw(renderer, camera);
    this->end.draw(renderer, camera);

    for (Zone check : this->checkpoints){
        check.draw(renderer, camera);
    }
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

    int x = start.getX();
    int y = start.getY();
    this->map[x][y] = Tuile(x, y, 20, "air");
    this->map[x+1][y] = Tuile(x+1, y, 20, "air");
    this->map[x][y+1] = Tuile(x, y+1, 20, "air");
    this->map[x+1][y+1] = Tuile(x+1, y+1, 20, "air");
    this->map[x][y+2] = Tuile(x, y+2, 20, "air");
    this->map[x+1][y+2] = Tuile(x+1, y+2, 20, "air");
}


Zone Map::getStart() {
    return this->start;
}


void Map::setEnd(Zone end) {
    this->end = end;

    int x = end.getX();
    int y = end.getY();
    this->map[x][y] = Tuile(x, y, 20, "air");
    this->map[x+1][y] = Tuile(x+1, y, 20, "air");
    this->map[x][y+1] = Tuile(x, y+1, 20, "air");
    this->map[x+1][y+1] = Tuile(x+1, y+1, 20, "air");
    this->map[x][y+2] = Tuile(x, y+2, 20, "air");
    this->map[x+1][y+2] = Tuile(x+1, y+2, 20, "air");
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


void Map::removeCheckpoint(int id) {
    this->checkpoints.erase(this->checkpoints.cbegin() + id);

    for (int i = 0; i < this->checkpoints.size(); i++){
        this->checkpoints[i].setId(i);
    }
}


void Map::resize(int mapW, int mapH) {
    std::vector<std::vector<Tuile>> copyMap = this->copyMap();

    if (mapW < 80){
        mapW = 80;
    }
    if (mapH < 45){
        mapH = 45;
    }
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

    // Changement de la place du début s'il n'est plus dans la map
    while (this->start.getX() <= 0){
        this->start.setPos(this->start.getX()+1, this->start.getY());
    }
    while (this->start.getX() >= this->map.size()-2){
        this->start.setPos(this->start.getX()-1, this->start.getY());
    }
    while (this->start.getY() <= 0){
        this->start.setPos(this->start.getX(), this->start.getY()+1);
    }
    while (this->start.getY() >= this->map[0].size()-3){
        this->start.setPos(this->start.getX(), this->start.getY()-1);
    }
    this->setStart(this->start);

    // Changement de la place de la fin s'il n'est plus dans la map
    while (this->end.getX() <= 0){
        this->end.setPos(this->end.getX()+1, this->end.getY());
    }
    while (this->end.getX() >= this->map.size()-2){
        this->end.setPos(this->end.getX()-1, this->end.getY());
    }
    while (this->end.getY() <= 0){
        this->end.setPos(this->end.getX(), this->end.getY()+1);
    }
    while (this->end.getY() >= this->map[0].size()-3){
        this->end.setPos(this->end.getX(), this->end.getY()-1);
    }
    this->setEnd(this->end);

    // On regarde quels checkpoints sont enn dehors de la map
    std::vector<int> idToRemove;
    for (Zone check : this->checkpoints){
        if (check.getX() <= 0 || check.getX() >= this->map.size()-2 || check.getY() <= 0 || check.getY() >= this->map[0].size()-3){
            idToRemove.push_back(check.getId());
        }
    }
    // Puis on les supprime
    for (int i = 0; i < idToRemove.size(); i++){
        this->removeCheckpoint(idToRemove[i]-i);
    }
}
