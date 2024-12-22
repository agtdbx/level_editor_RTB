//
// Created by auguste on 28/05/2022.
//

#include "../include/Menu.h"
#include "../include/Functions.h"
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <json/json.h>
#include <json/value.h>
#include <json/writer.h>
#include <json/reader.h>
#include <dirent.h>


//Private methods
void Menu::initButton() {
    SDL_Color colorOff = {255, 255, 255, 0};
    SDL_Color colorOn = {200, 200, 200, 100};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color blue = {0, 0, 255, 100};
    SDL_Color writeColor = {100, 100, 255, 100};


    //Menu principal
    this->butCreer   = Button((char *)"Creer"  , 40, 1, this->winW/2 - 100, this->winH/2 - 150, 200, 50, colorOff, colorOn, 2, black);
    this->butCharger = Button((char *)"Charger", 40, 1, this->winW/2 - 100, this->winH/2 - 50 , 200, 50, colorOff, colorOn, 2, black);
    this->butOptions = Button((char *)"Options", 40, 1,this->winW/2 - 100 , this->winH/2 + 50 , 200, 50, colorOff, colorOn, 2, black);
    this->butQuitter = Button((char *)"Quitter", 40, 1, this->winW/2 - 100, this->winH/2 + 150, 200, 50, colorOff, colorOn, 2, black);

    //Création d'une nouvelle map
    this->inputNewName = Input((char *)"Nom de la map", 40, 1,20, false, this->winW/2 - 250, this->winH/2 - 100, 500, 50, colorOff, colorOn,2, black, writeColor);
    this->inputNewW = Input((char *)"Largeur", 40, 1,3, true, this->winW/2 - 175, this->winH/2, 150, 50, colorOff, colorOn,2, black, writeColor);
    this->inputNewH = Input((char *)"Hauteur", 40, 1,3, true, this->winW/2 + 25, this->winH/2, 150, 50, colorOff, colorOn,2, black, writeColor);
    this->butValiderCreer = Button((char *)"Valider", 40, 1, this->winW/2 - 100, this->winH/2 + 100, 200, 50, colorOff, colorOn,2, black);
    this->butRetourCreer = Button((char *)"Retour", 40, 1, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, black);

    // Chargement
    this->inputLoadName = Input((char *)"Nom du fichier", 40, 1,20, false, this->winW/2 - 250, this->winH/2 - 100, 500, 50, colorOff, colorOn,2, black, writeColor);
    this->butValiderCharger = Button((char *)"Valider", 40, 1, this->winW/2 - 100, this->winH/2 + 100, 200, 50, colorOff, colorOn,2, black);
    this->butRetourCharger = Button((char *)"Retour", 40, 1, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, black);

    //Options
    //Graphic
    this->butGraphics = Button((char *)"Graphique", 30, 2, this->spacingWithScreen + this->borderSize, 75 + this->spacingWithScreen, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);
    std::vector<char*> choixRes = { (char *)"1280x720",
                                    (char *)"1280x800",
                                    (char *)"1920x1080",
                                    (char *)"2560x1440"};

    this->butChoixRes = Select((char *)"1920x1080", 30, 1, this->winW/2 + 110, 250, 160, 40, colorOff, colorOn, choixRes, 2, black);
    this->fullScreen = Switch(this->winW/2 - 20, 340, 80, 20, colorOff, blue, 2, black);

    //Credit
    this->butCredit = Button((char *)"Credit", 30,2, this->spacingWithScreen + this->borderSize, 75*2 + this->spacingWithScreen - this->borderSize, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);

    this->butRetourOptions = Button((char *)"Retour", 40, 1, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, black);
}


void Menu::input() {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                this->run = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    if (this->fenetre != 0){
                        this->fenetre = 0;
                    }
                    else{
                        this->run = false;
                    }
                }
                if (event.key.keysym.sym == SDLK_LSHIFT){
                    this->inputNewName.setShift(true);
                    this->inputLoadName.setShift(true);
                }
                if (fenetre == 1){
                    if (this->inputNewName.getWrite()){
                        this->inputNewName.giveInput(event.key.keysym.sym);
                    }
                    else if (this->inputNewW.getWrite()){
                        this->inputNewW.giveInput(event.key.keysym.sym);
                    }
                    else if (this->inputNewH.getWrite()){
                        this->inputNewH.giveInput(event.key.keysym.sym);
                    }
                }
                if (fenetre == 3){
                    if (this->inputLoadName.getWrite()){
                        this->inputLoadName.giveInput(event.key.keysym.sym);
                    }
                }
                break;

            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_LSHIFT){
                    this->inputNewName.setShift(false);
                    this->inputLoadName.setShift(false);
                }
                break;
        }
    }
}


void Menu::tick() {
    switch (this->fenetre) {
        case 0:
            if (this->butCreer.clicOnButton()){
                fenetre = 1;
            }
            else if (this->butCharger.clicOnButton()){
                fenetre = 3;
            }
            else if (this->butOptions.clicOnButton()){
                fenetre = 20;
            }
            else if (this->butQuitter.clicOnButton()){
                this->run = false;
            }
            break;

        case 1:
            if (this->butValiderCreer.clicOnButton()){
                if (!this->inputNewName.isEmpty() && !this->inputNewW.isEmpty() && !this->inputNewH.isEmpty()){
                    char * cw = this->inputNewW.getValue();
                    char * ch = this->inputNewH.getValue();
                    int w = atoi(cw);
                    int h = atoi(ch);
                    if (w <= 80){
                        w = 80;
                    }
                    if (h <= 45){
                        h = 45;
                    }
                    this->map = Map(w, h, 20);
                    this->mapname = this->inputNewName.getValue();

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

                    this->fenetre = 0;
                    this->run = false;
                    this->continuer = true;
                }
            }
            else if (this->butRetourCreer.clicOnButton()){
                this->fenetre = 0;
            }
            break;

        case 20:
            if(this->butCredit.clicOnButton()){
                fenetre = 23;
            }
            else if (this->butRetourOptions.clicOnButton()){
                this->fenetre = 0;
            }
            break;

        case 23:
            if (this->butGraphics.clicOnButton()){
                fenetre = 20;
            }
            else if (this->butRetourOptions.clicOnButton()){
                this->fenetre = 0;
            }
            break;

        case 3:
            if (this->butValiderCharger.clicOnButton()){
                if (!this->inputLoadName.isEmpty()){
                    this->filename = this->inputLoadName.getValue();
                    if (loadMap()){
                        this->fenetre = 0;
                        this->run = false;
                        this->continuer = true;
                    }
                }
            }
            else if (this->butRetourCharger.clicOnButton()){
                this->fenetre = 0;
            }
            break;
    }
}


void Menu::render() {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);

    SDL_Color color = {0, 0, 0, 255};
    switch (this->fenetre) {
        case 0:
            drawText(this->renderer, (char *)"RTB Editor !", 80, this->winW/2, 50, 1, color);
            this->butCreer.draw(this->renderer);
            this->butCharger.draw(this->renderer);
            this->butOptions.draw(this->renderer);
            this->butQuitter.draw(this->renderer);

            break;

        case 1:
            drawText(this->renderer, (char *)"RTB Editor !", 80, this->winW/2, 50, 1, color);

            this->inputNewName.draw(this->renderer);
            this->inputNewW.draw(this->renderer);
            this->inputNewH.draw(this->renderer);
            this->butValiderCreer.draw(this->renderer);
            this->butRetourCreer.draw(this->renderer);
            break;

        case 20:{
            drawText(this->renderer, (char *)"RTB Editor !", 80, this->winW/2, 10, 1, color);
            drawText(this->renderer, (char *)"Options graphique", 50, this->winW/2, 100, 1, color);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75 + this->spacingWithScreen, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawGraphicOptions();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 23:{
            drawText(this->renderer, (char *)"RTB Editor !", 80, this->winW/2, 10, 1, color);
            drawText(this->renderer, (char *)"Credit", 50, this->winW/2, 100, 1, color);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75*2 + this->spacingWithScreen - this->borderSize, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawCredit();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 3:
            drawText(this->renderer, (char *)"RTB Editor !", 80, this->winW/2, 50, 1, color);

            this->inputLoadName.draw(this->renderer);
            this->butValiderCharger.draw(this->renderer);
            this->butRetourCharger.draw(this->renderer);
            break;
    }

    SDL_RenderPresent(this->renderer);
}

void Menu::drawBaseOptions() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    int x = 0;
    int y = 0;
    int width = 250;
    int height = 75;
    //Case en haut à gauche
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    SDL_Color color = {0, 0, 0, 255};
    drawText(this->renderer, (char *)"Options", 40, x+width/2+this->spacingWithScreen+this->borderSize, y+ height/6 +this->spacingWithScreen+this->borderSize, 1, color);

    //Case exterieure
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {0+this->spacingWithScreen+i, 0+this->spacingWithScreen+i, 250-i*2, winH-this->spacingWithScreen*2-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }

    //Case graphique
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    y = height - this->borderSize;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butGraphics.draw(this->renderer);

    //Case credit
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    y = height*2 - this->borderSize*2;
    for (int i = 0; i < this->borderSize; ++i){
        SDL_Rect rect = {x+this->spacingWithScreen+i, y+this->spacingWithScreen+i, width-i*2, height-i*2};
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    this->butCredit.draw(this->renderer);
}


void Menu::drawGraphicOptions() {
    SDL_Color color = {0, 0, 0, 255};

    //Choix résolution
    drawText(this->renderer, (char *)"Resolution de l'ecran :", 30, this->winW/2 - 200, 250, 0, color);
    bool changeChoix = this->butChoixRes.draw(this->renderer);

    if (changeChoix){
        this->setScreenSize();
    }

    //Pleins écran
    drawText(this->renderer, (char *)"Plein ecran :", 30, this->winW/2 - 200, 330, 0, color);
    bool fullScreen = this->fullScreen.draw(this->renderer);

    if (fullScreen){
        this->setScreenMode();
    }
}

void Menu::drawCredit() {

}


void Menu::setScreenSize() {
    char *res = this->butChoixRes.getValue();
    std::string width, height;
    bool first = false;

    for (int i = 0; i < strlen(res); ++i){
        if (res[i] == 'x'){
            first = true;
        }
        else if (!first){
            width.push_back(res[i]);
        }
        else{
            height.push_back(res[i]);
        }
    }
    std::stringstream intWidth(width);
    std::stringstream intHeight(height);

    intWidth >> this->winW;
    intHeight >> this->winH;

    SDL_SetWindowSize(this->window, this->winW, this->winH);

    this->butChoixRes.setX(this->winW/2 + 110);
    this->fullScreen.setX(this->winW/2 - 20);

    //Menu principal
    this->butCreer.setX(this->winW/2 - 100);
    this->butCreer.setY(this->winH/2 - 150);
    this->butCharger.setX(this->winW/2 - 100);
    this->butCharger.setY(this->winH/2 - 50);
    this->butOptions.setX(this->winW/2 - 100);
    this->butOptions.setY(this->winH/2 + 50);
    this->butQuitter.setX(this->winW/2 - 100);
    this->butQuitter.setY(this->winH/2 + 150);

    //Création d'une nouvelle map
    this->inputNewName.setX(this->winW/2 - 250);
    this->inputNewName.setY(this->winH/2 - 100);
    this->inputNewW.setX(this->winW/2 - 175);
    this->inputNewW.setY(this->winH/2);
    this->inputNewH.setX(this->winW/2 + 25);
    this->inputNewH.setY(this->winH/2);
    this->butValiderCreer.setX(this->winW/2 -100);
    this->butValiderCreer.setY(this->winH/2 + 100);
    this->butRetourCreer.setX(this->winW/2 - 100);
    this->butRetourCreer.setY(this->winH-50 - 100);

    // Chargement
    this->inputLoadName.setX(this->winW/2 - 250);
    this->inputLoadName.setY(this->winH/2 - 100);
    this->butValiderCharger.setX(this->winW/2 - 100);
    this->butValiderCharger.setY(this->winH/2 + 100);
    this->butRetourCharger.setX(this->winW/2 - 100);
    this->butRetourCharger.setY(this->winH-50 - 100);

    //Options
    //Graphic
    this->butChoixRes.setX(this->winW/2 + 110);
    this->fullScreen.setX(this->winW/2 - 20);

    this->butRetourOptions.setX(this->winW/2 - 100);
    this->butRetourOptions.setY(this->winH-50 - 100);
}


void Menu::setScreenMode() {
    if (this->fullScreen.isActive()){
        SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    else{
        SDL_SetWindowFullscreen(this->window, SDL_WINDOW_SHOWN);
    }
}


void Menu::saveOptions() {
    Json::Value json;
    // Sauvegarde des options
    std::ofstream myfile;
    myfile.open ("./data/saves/options.json"); // Ouverture du fichier

    json["resolution"] = this->butChoixRes.getValue();
    json["winW"] = this->winW;
    json["winH"] = this->winH;
    json["fullscreen"] = this->fullScreen.isActive();

    Json::StyledWriter writer;
    myfile << writer.write(json);

    myfile.close();
}


void Menu::loadOptions() {
    Json::Value json;
    Json::Reader reader;
    std::ifstream myfile ("./data/saves/options.json");// Ouverture du fichier
    reader.parse(myfile, json);

    this->butChoixRes.setValue(json["resolution"].asString());
    this->winW = json["winW"].asInt();
    this->winH = json["winH"].asInt();
    this->fullScreen.setActive(json["fullscreen"].asBool());

    myfile.close();
}


bool Menu::loadMap() {
    std::string file = "";
    file.append(this->filename);
    file.append(".json");

    bool test = false;
    DIR *d;
    struct dirent *dir;
    d = opendir("../../RTB/data/levels/");
    if (d){
        while ((dir = readdir(d)) != NULL){
            std::string file_name = dir->d_name;
            if (file_name != "." && file_name != ".."){
                if (file_name == file){
                    test = true;
                }
            }
        }
        closedir(d);
    }

    if (test){
        Json::Value json;
        Json::Reader reader;

        std::string filepath = "../../RTB/data/levels/";
        filepath.append(file);

        std::ifstream myfile(filepath);

        reader.parse(myfile, json); // Récupération du fichier
        std::string fname = json["filename"].asString();
        std::string mname = json["name"].asString();
        this->filename = json["filename"].asString();
        this->mapname = json["name"].asString();

        int w = json["width"].asInt();
        int h = json["heigth"].asInt();
        int size = json["square_size"].asInt();
        this->map = Map(w, h, size);

        // Chargement du debut
        Json::Value debut = json["start"];
        Zone start = Zone(debut["x"].asInt(), debut["y"].asInt(), "start");
        this->map.setStart(start);

        // Chargement de la fin
        Json::Value fin = json["end"];
        Zone end = Zone(fin["x"].asInt(), fin["y"].asInt(), "end");
        this->map.setEnd(end);

        // Chargement des checkpoints
        Json::Value checkpoints = json["checkpoints"];
        if (checkpoints.isArray()){
            for (int i = 0; i < checkpoints.size(); i++){
                Json::Value check = checkpoints[i];

                int x = check["x"].asInt();
                int y = check["y"].asInt();
                int id = check["id"].asInt();

                Zone checkpoint = Zone(x, y, id);
                this->map.addCheckpoint(checkpoint);
            }
        }

        Json::Value tuiles = json["map"];
        for (int i = 0; i < tuiles.size(); i++){
            Json::Value t = tuiles[i];

            int x = t["x"].asInt();
            int y = t["y"].asInt();
            std::string type = t["type"].asString();

            Tuile tuile = Tuile(x, y, size, const_cast<char*>(type.c_str()));
            this->map.set(x, y, tuile);
        }

        return true;
    }

    return false;
}


//Public methods
Menu::Menu(SDL_Window *window, SDL_Renderer *renderer, int winW, int winH) {
    this->winW = winW;
    this->winH = winH;
    this->window = window;
    this->renderer = renderer;
    this->run = true;
    this->fenetre = 0;
    this->continuer = false;
    this->spacingWithScreen = 10;
    this->borderSize = 3;
    this->lastClic = 0.0;
    this->lastTime = 0.0;
    this->map = Map();
    this->mapname = "";
    this->filename = "";

    this->initButton();

    this->loadOptions();

    this->setScreenSize();
    this->setScreenMode();
}


Menu::~Menu() {

}


bool Menu::start() {
    this->run = true;
    this->continuer = false;

    while(this->run){
        if (((float)SDL_GetTicks()/1000) - this->lastTime > 1.0/30){
            this->lastTime = (float)SDL_GetTicks()/1000;
            this->input();
            this->tick();
            this->render();
        }
    }
    this->saveOptions();

    float wait = (float)SDL_GetTicks()/1000.0f;
    while ((float)SDL_GetTicks()/1000.0f - wait < 0.2){}

    return this->continuer;
}


int Menu::getWinWidth() {
    return this->winW;
}


int Menu::getWinHeight() {
    return this->winH;
}

Map Menu::getMap() {
    return this->map;
}

std::string Menu::getMapname() {
    return this->mapname;
}

std::string Menu::getFilename()
{
    return this->filename;
}
