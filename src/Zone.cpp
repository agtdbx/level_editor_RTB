//
// Created by auguste on 09/08/22.
//

#include "../include/Zone.h"
#include "../include/Functions.h"

// Private methods


// Public methods
Zone::Zone() {
    this->x = 0;
    this->y = 0;
    this->w = 2;
    this->h = 3;
    this->id = 0;
    this->color = {120, 120, 120, 255};
}


Zone::Zone(int x, int y, std::string type) {
    this->x = x;
    this->y = y;
    this->w = 2;
    this->h = 3;
    this->id = 0;

    if (type == "start"){
        this->color = {200, 50, 50, 255};
    }
    else if (type == "end"){
        this->color = {50, 50, 200, 255};
    }
    else{
        this->color = {120, 120, 120, 255};
    }
}


Zone::Zone(int x, int y, int id) {
    this->x = x;
    this->y = y;
    this->w = 2;
    this->h = 3;
    this->id = id;
    this->color = {50, 200, 50, 255};
}


Zone::~Zone() {

}


void Zone::draw(SDL_Renderer *renderer, Camera camera) {
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    int x = this->x * 20 - camera.getX();
    int y = this->y * 20 - camera.getY();
    SDL_Rect rect = {x, y, this->w * 20, this->h * 20};
    SDL_RenderFillRect(renderer, &rect);

    if (this->color.r == 200){
        drawText(renderer, "D", 20, x + this->w*10, y, 2, {0, 0, 0, 255});
    }
    else if (this->color.g == 200){
        std::string id = std::to_string(this->id);
        char* idStr = const_cast<char*>(id.c_str());
        drawText(renderer, idStr, 20, x + this->w*10, y, 2, {0, 0, 0, 255});
    }
    else if (this->color.b == 200){
        drawText(renderer, "F", 20, x + this->w*10, y, 2, {0, 0, 0, 255});
    }
}


bool Zone::inZone(int tx, int ty) {
    return tx >= this->x && tx < this->x + this->w && ty >= this->y && ty < this->y + this->h;
}


int Zone::getX() {
    return this->x;
}


int Zone::getY() {
    return this->y;
}


int Zone::getId() {
    return this->id;
}


void Zone::setId(int id) {
    this->id = id;
}