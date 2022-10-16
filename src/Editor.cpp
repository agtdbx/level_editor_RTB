//
// Created by auguste on 31/05/22.
//

#include "../include/Editor.h"
#include "../include/Functions.h"
#include <SDL2/SDL.h>
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
    this->butContinuer = Button((char *)"Retour", 40, 1, this->winW/2 - 100, this->winH/2 - 75, 200, 50, colorOff, colorOn,2, black);
    this->butQuitAndSave = Button((char *)"Quitter et sauvegarder", 40, 1, this->winW/2 - 225, this->winH/2 + 25, 450, 50, colorOff, colorOn,2, black);
    this->butQuitNoSave = Button((char *)"Quitter sans sauvegarder", 40, 1, this->winW/2 - 250, this->winH/2 + 125, 500, 50, colorOff, colorOn,2, black);
    this->butRetourMenu = Button((char *)"Retour au menu", 40, 1, this->winW/2 - 150, this->winH/2 - 75, 300, 50, colorOff, colorOn,2, black);
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
        this->editorBar.input(event);
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
        this->editorBar.tick();
        this->mouseClic();

        if (this->map.getWidth() != this->editorBar.getMapW() || this->map.getHeigth() != this->editorBar.getMapH()){
            this->map.resize(this->editorBar.getMapW(), this->editorBar.getMapH());
        }
    }
    else if (this->fenetre == 1) {
        if (this->butContinuer.clicOnButton()){
            this->fenetre = 0;
        }
        else if (this->butQuitAndSave.clicOnButton()){
            this->run = false;
        }
        else if (this->butQuitNoSave.clicOnButton()){
            this->run = false;
            this->exitWithSave = false;
        }
    }
    this->lastTime = ((float)SDL_GetTicks()/1000.0f);
}


void Editor::render() {
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);

    this->map.draw(this->renderer, this->camera, this->winW, this->winH);
    this->editorBar.draw(this->renderer);

    if (this->mouseTarget){
        int x = this->mouseTargetX*20 - this->camera.getX();
        int y = this->mouseTargetY*20 - this->camera.getY();

        if (this->map.get(this->mouseTargetX, this->mouseTargetY).getType() == "mur"){
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        }
        else{
            SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        }

        int choice = this->editorBar.getChoice();

        if (choice >= 0){
            SDL_Rect rect = {x, y, 20, 20};
            SDL_Rect rect2 = {x+1, y+1, 18, 18};
            SDL_RenderDrawRect(this->renderer, &rect);
            SDL_RenderDrawRect(this->renderer, &rect2);
        }
        else{
            SDL_Rect rect = {x, y, 40, 60};
            SDL_Rect rect2 = {x+1, y+1, 38, 58};
            SDL_RenderDrawRect(this->renderer, &rect);
            SDL_RenderDrawRect(this->renderer, &rect2);
        }
    }

    switch (this->fenetre) {
        case 0:
            break;

        case 1:
            this->butContinuer.draw(this->renderer);
            this->butQuitAndSave.draw(this->renderer);
            this->butQuitNoSave.draw(this->renderer);
            break;
    }

    SDL_RenderPresent(this->renderer);
}


void Editor::saveMap() {
    if (this->mapname != this->editorBar.getMapname()){
        this->mapname = this->editorBar.getMapname();

        this->filename = "";
        for (int i = 0; i < this->mapname.size(); i++){
            char c = this->mapname[i];
            if (c == ' ' || c == '-'){
                this->filename.push_back('_');
            }
            else if (c != '&'){
                this->filename.push_back(c);
            }
        }
    }

    Json::Value json;
    // Sauvegarde des options
    std::ofstream myfile;
    std::string file = "../RTB/data/levels/";
    file.append(this->filename);
    file.append(".json");
    myfile.open(file, std::fstream::out); // Ouverture du fichier

    json["name"] = this->mapname;
    json["filename"] = this->filename;
    json["width"] = this->map.getWidth();
    json["heigth"] = this->map.getHeigth();
    json["square_size"] = this->map.getSquarreSize();

    // Sauvegarde du debut
    Json::Value debut;
    Zone start = this->map.getStart();
    debut["x"] = start.getX();
    debut["y"] = start.getY();
    json["start"] = debut;

    // Sauvegarde de la fin
    Json::Value fin;
    Zone end = this->map.getEnd();
    fin["x"] = end.getX();
    fin["y"] = end.getY();
    json["end"] = fin;

    // Sauvegarde des checkpoints
    Json::Value checks;
    std::vector<Zone> checkpoints = this->map.getCheckpoint();
    for (int i = 0; i < checkpoints.size(); i++){
        Zone checkpoint = checkpoints[i];
        Json::Value check;
        check["x"] = checkpoint.getX();
        check["y"] = checkpoint.getY();
        check["id"] = checkpoint.getId();
        checks.append(check);
    }
    json["checkpoints"] = checks;

    // Sauvegarde de la map
    Json::Value map;
    for (int x = 0; x < this->map.getWidth(); x++){
        for (int y = 0; y < this->map.getHeigth(); y++){
            Json::Value tuile;
            Tuile t = this->map.get(x, y);

            tuile["x"] = x;
            tuile["y"] = y;
            tuile["type"] = t.getType();

            map.append(tuile);
        }
    }

    json["map"] = map;

    Json::StyledWriter writer;
    myfile << writer.write(json);

    myfile.close();
}


void Editor::mouseClic() {
    int x, y;
    Uint32 buttons;

    SDL_PumpEvents();  // make sure we have the latest mouse state.

    buttons = SDL_GetMouseState(&x, &y);

    if (x >= 300){
        int tx = (x + this->camera.getX())/20;
        int ty = (y + this->camera.getY())/20;

        this->mouseTarget = true;
        this->mouseTargetX = tx;
        this->mouseTargetY = ty;

        if (tx > 0 && tx < this->map.getWidth()-1 && ty > 0 && ty < this->map.getHeigth()-1){
            if ((buttons & SDL_BUTTON_LMASK) != 0){
                if (this->editorBar.getFen() == 0){
                    int choice = this->editorBar.getChoice();
                    if (choice >= 0){
                        if (!this->map.getStart().inZone(tx, ty) & !this->map.getEnd().inZone(tx, ty)){
                            int checkId = -1;

                            for (Zone check : this->map.getCheckpoint()){
                                if (check.inZone(tx, ty)){
                                    checkId = check.getId();
                                    break;
                                }
                            }

                            if (checkId == -1){
                                std::string type = "mur";

                                switch (choice) {
                                    case 0:
                                        type = "mur";
                                        break;

                                    case 1:
                                        type = "air";
                                        break;

                                    case 2:
                                        type = "slime";
                                        break;

                                    case 3:
                                        type = "glace";
                                        break;

                                    case 4:
                                        type = "pique";
                                        break;

                                    case 5:
                                        type = "plateforme";
                                        break;

                                    case 6:
                                        type = "eau";
                                        break;
                                }
                                Tuile t = Tuile(tx, ty, 20, type);
                                this->map.set(tx, ty, t);
                            }
                            else{
                                this->map.removeCheckpoint(checkId);
                            }
                        }
                    }
                    else{
                        if (tx > 0 && tx < this->map.getWidth()-2 && ty > 0 && ty < this->map.getHeigth()-3){
                            if (choice == -1){
                                Zone start = Zone(tx, ty, "start");
                                this->map.setStart(start);
                            }
                            else if (choice == -2){
                                Zone end = Zone(tx, ty, "end");
                                this->map.setEnd(end);
                            }
                            else if (choice == -3){
                                int id = this->map.getCheckpoint().size();
                                Zone check = Zone(tx, ty, id);
                                this->map.addCheckpoint(check);
                                float wait = (float)SDL_GetTicks()/1000.0f;
                                while ((float)SDL_GetTicks()/1000.0f - wait < 0.2){}
                            }
                        }
                    }
                }
            }
        }
        else{
            this->mouseTarget = false;
        }
    }
    else{
        this->mouseTarget = false;
    }
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
    this->editorBar = EditorBar(winW, winH, this->mapname, 0, 0);

    this->initButton();
}


Editor::~Editor() {

}


void Editor::start() {
    this->run = true;
    this->fenetre = 0;

    this->exitWithSave = true;

    this->mouseTarget = false;
    this->mouseTargetX = 0;
    this->mouseTargetY = 0;

    this->camera.setPos(-300.0f, 0.0f);

    while(this->run){
        if (((float)SDL_GetTicks()/1000) - this->lastTime >= 1.0f/30.0f){
            this->input();
            this->tick();
            this->render();
        }
    }
    float wait = (float)SDL_GetTicks()/1000.0f;
    while ((float)SDL_GetTicks()/1000.0f - wait < 0.2){}

    if (exitWithSave){
        saveMap();
    }
}

void Editor::setVariables(int winWidth, int winHeight, Map map, std::string mapname, std::string filename) {
    this->winW = winWidth;
    this->winH = winHeight;
    this->map = map;
    this->mapname = mapname;
    this->filename = filename;
    this->editorBar = EditorBar(winW, winH, this->mapname, this->map.getWidth(), this->map.getHeigth());

    this->butContinuer.setX(this->winW/2 - 100);
    this->butContinuer.setY(this->winH/2 - 75);
    this->butQuitAndSave.setX(this->winW/2 - 225);
    this->butQuitAndSave.setY(this->winH/2 + 25);
    this->butQuitNoSave.setX(this->winW/2 - 250);
    this->butQuitNoSave.setY(this->winH/2 + 125);
}