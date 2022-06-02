//
// Created by auguste on 31/05/22.
//

#include "../include/Editor.h"
#include "../include/Functions.h"
#include <SDL.h>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/reader.h>
//Private methods
void Editor::initButton() {
    SDL_Color colorOff = {255, 255, 255, 100};
    SDL_Color colorOn = {200, 200, 200, 150};
    SDL_Color black = {0, 0, 0, 255};
    this->butContinuer = Button("Continuer", 40, 1, this->winW/2 - 100, this->winH/2 - 75, 200, 50, colorOff, colorOn,2, black);
    this->butQuitter = Button("Quitter", 40, 1, this->winW/2 - 100, this->winH/2 + 25, 200, 50, colorOff, colorOn,2, black);
    this->butRetourMenu = Button("Retour au menu", 40, 1, this->winW/2 - 150, this->winH/2 - 75, 300, 50, colorOff, colorOn,2, black);
}

void Editor::input() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                this->run = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE && this->fenetre != 2){
                    if (this->fenetre == 0){
                        this->fenetre = 1;
                    }
                    else{
                        this->fenetre = 0;
                    }
                }
                break;
        }
    }
}


void Editor::tick() {
    if (this->fenetre == 0){
        int keylen;
        const unsigned char *keyboard = SDL_GetKeyboardState(&keylen);

        float delta = ((float)SDL_GetTicks()/1000.0f) - this->lastTime;

        float cameraSpeed = 500.0f * delta;

        if (keyboard[SDL_SCANCODE_UP]) {
            this->camera.addPosY(-cameraSpeed);
        }
        if (keyboard[SDL_SCANCODE_DOWN]) {
            this->camera.addPosY(cameraSpeed);
        }
        if (keyboard[SDL_SCANCODE_LEFT]) {
            this->camera.addPosX(-cameraSpeed);
        }
        if (keyboard[SDL_SCANCODE_RIGHT]) {
            this->camera.addPosX(cameraSpeed);
        }


    }
    else if (this->fenetre == 1) {
        if (this->butContinuer.clicOnButton()){
            this->fenetre = 0;
        }
        else if (this->butQuitter.clicOnButton()){
            this->run = false;
        }
    }
    else{
        if (this->butRetourMenu.clicOnButton()){
            this->run = false;
        }
    }
    this->lastTime = ((float)SDL_GetTicks()/1000.0f);
}


void Editor::render() {
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);

    this->map.draw(this->renderer, this->camera, this->winW, this->winH);

    switch (this->fenetre) {
        case 0:
            break;

        case 1:
            this->butContinuer.draw(this->renderer);
            this->butQuitter.draw(this->renderer);
            break;

        case 2:
            this->butRetourMenu.draw(this->renderer);
    }

    SDL_RenderPresent(this->renderer);
}


void Editor::saveMap() {

}


//Public methods
Editor::Editor(SDL_Renderer *renderer, int winW, int winH) {
    this->winW = winW;
    this->winH = winH;
    this->renderer = renderer;
    this->run = true;
    this->fenetre = 0;
    this->lastTime = ((float)SDL_GetTicks()/1000.0f);
    this->camera = Camera();
    this->mapname = "";
    this->filename = "";

    this->initButton();
}


Editor::~Editor() {
    Json::Value json;
    // Sauvegarde des options
    std::ofstream myfile;
    std::string file = "../data/levels/";
    file.append(this->filename);
    file.append(".json");
    myfile.open(file, std::fstream::out); // Ouverture du fichier

    json["name"] = this->mapname;
    json["filename"] = this->filename;
    json["width"] = this->map.getWidth();
    json["heigth"] = this->map.getHeigth();
    json["square_size"] = this->map.getSquarreSize();

    Json::Value checks;
    std::vector<Checkpoint> checkpoints = this->map.getCheckpoint();
    for (int i = 0; i < checkpoints.size(); i++){
        Checkpoint checkpoint = checkpoints[i];
        Json::Value check;
        check["x"] = checkpoint.getX();
        check["y"] = checkpoint.getY();
        check["id"] = checkpoint.getId();
        checks.append(check);
    }
    json["checkpoints"] = checks;

    Json::Value map;
    for (int x = 0; x < this->map.getWidth(); x++){
        for (int y = 0; y < this->map.getHeigth(); y++){
            Json::Value tuile;
            Tuile t = this->map.get(x, y);

            tuile["x"] = x;
            tuile["y"] = y;
            tuile["type"] = t.getType();

            SDL_Color color = t.getColor();
            tuile["r"] = color.r;
            tuile["g"] = color.g;
            tuile["b"] = color.b;
            tuile["a"] = color.a;

            map.append(tuile);
        }
    }

    json["map"] = map;

    Json::StyledWriter writer;
    myfile << writer.write(json);

    myfile.close();
}


void Editor::start() {
    this->run = true;
    this->fenetre = 0;
    while(this->run){
        if (((float)SDL_GetTicks()/1000) - this->lastTime >= 1.0f/30.0f){
            this->input();
            this->tick();
            this->render();
        }
    }
    float wait = (float)SDL_GetTicks()/1000.0f;
    while ((float)SDL_GetTicks()/1000.0f - wait < 0.2){}

    saveMap();
}

void Editor::setVariables(int winWidth, int winHeight, Map map, char* mapname, char* filename) {
    this->winW = winWidth;
    this->winH = winHeight;
    this->map = map;
    this->mapname = mapname;
    this->filename = filename;

    this->butContinuer.setX(this->winW/2 - 100);
    this->butContinuer.setY(this->winH/2 - 75);
    this->butQuitter.setX(this->winW/2 - 100);
    this->butQuitter.setY(this->winH/2 + 25);
}