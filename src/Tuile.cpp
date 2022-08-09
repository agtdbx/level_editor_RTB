//
// Created by auguste on 31/05/22.
//

#include <iostream>
#include <string>
#include "../include/Tuile.h"


// private methodes



// public methodes
Tuile::Tuile() {
    this->x = 0;
    this->y = 0;
    this->size = 10;
    this->type = "mur";
    this->color = {100, 100, 100, 255};
}


Tuile::Tuile(int x, int y, int size, std::string type) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->type = type;

    if (this->type == "mur") {
        this->color = {0, 0, 0, 255};
    }
    if (this->type == "air") {
        this->color = {255, 255, 255, 255};
    }
    if (this->type == "slime") {
        this->color = {0, 255, 0, 255};
    }
    if (this->type == "glace") {
        this->color = {0, 255, 255, 255};
    }
    if (this->type == "pique") {
        this->color = {100, 100, 100, 255};
    }
}


Tuile::~Tuile() {

}


void Tuile::draw(SDL_Renderer *renderer, Camera camera) {
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    int x = this->x*this->size - camera.getX();
    int y = this->y*this->size  - camera.getY();
    SDL_Rect rect = {x, y, this->size, this->size};
    SDL_RenderFillRect(renderer, &rect);
}


bool Tuile::isPassable() {
    if (this->type == "air" || this->type == "pique") {
        return true;
    }
    return false;
}


int Tuile::touch() {
    if (this->type == "mur") {
        return 0;
    }
    if (this->type == "air") {
        return 1;
    }
    if (this->type == "slime") {
        return 2;
    }
    if (this->type == "glace") {
        return 3;
    }
    if (this->type == "pique") {
        return 4;
    }
    return -1;
}


std::string Tuile::getType() {
    return this->type;
}


SDL_Color Tuile::getColor() {
    return this->color;
}