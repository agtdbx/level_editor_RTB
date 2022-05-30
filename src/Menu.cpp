//
// Created by auguste on 28/05/2022.
//

#include "../include/Menu.h"
#include "../include/Functions.h"
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/reader.h>

//Private methods

void Menu::initButton() {
    SDL_Color colorOff = {255, 255, 255, 0};
    SDL_Color colorOn = {200, 200, 200, 100};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color blue = {0, 0, 255, 100};

    //Menu principal
    this->butCreer   = Button("Creer"  , 40, 1, this->winW/2 - 100, this->winH/2 - 150, 200, 50, colorOff, colorOn, 2, black);
    this->butCharger = Button("Charger", 40, 1, this->winW/2 - 100, this->winH/2 - 50 , 200, 50, colorOff, colorOn, 2, black);
    this->butOptions = Button("Options", 40, 1,this->winW/2 - 100 , this->winH/2 + 50 , 200, 50, colorOff, colorOn, 2, black);
    this->butQuitter = Button("Quitter", 40, 1, this->winW/2 - 100, this->winH/2 + 150, 200, 50, colorOff, colorOn, 2, black);

    //Création d'une nouvelle map
    this->inputNewName = Input("Nom de la map", 40, 1, this->winW/2 - 200, this->winH/2 - 100, 400, 50, colorOff, colorOn,2, black);
    this->butRetourCreer = Button("Retour", 40, 1, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, black);

    // Chargement
    this->butRetourCharger = Button("Retour", 40, 1, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, black);

    //Options
    //Graphic
    this->butGraphics = Button("Graphique", 30, 2, this->spacingWithScreen + this->borderSize, 75 + this->spacingWithScreen, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);
    std::vector<char*> choixRes = {"1280x720", "1280x800", "1920x1080", "2560x1440"};

    this->butChoixRes = Select("1920x1080", 30, 1, this->winW/2 + 110, 250, 160, 40, colorOff, colorOn, choixRes, 2, black);
    this->fullScreen = Switch(this->winW/2 - 20, 340, 80, 20, colorOff, blue, 2, black);

    //Credit
    this->butCredit = Button("Credit", 30,2, this->spacingWithScreen + this->borderSize, 75*2 + this->spacingWithScreen - this->borderSize, 250-this->borderSize*2, 75-this->borderSize*2, colorOff, colorOn,0, black);

    this->butRetourOptions = Button("Retour", 40, 1, this->winW/2 - 100, this->winH-50 - 100, 200, 50, colorOff, colorOn,2, black);
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
                if ((event.key.keysym.sym >= 48 && event.key.keysym.sym <= 57) || (event.key.keysym.sym >= 97 && event.key.keysym.sym <= 122) || event.key.keysym.sym == 8 || event.key.keysym.sym == 32){
                    if (fenetre == 3){
                        if (this->inputNewName.getWrite()){
                            this->inputNewName.giveInput(event.key.keysym.sym);
                        }
                    }
                }

                char c = event.key.keysym.sym;
                std::cout << "Autre : " << event.key.keysym.sym << " -> " << c << std::endl;

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
            if (this->butRetourCreer.clicOnButton()){
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
            if (this->butRetourCharger.clicOnButton()){
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
            drawText(this->renderer, "RTB Editor !", 80, this->winW/2, 50, 1, color);
            this->butCreer.draw(this->renderer);
            this->butCharger.draw(this->renderer);
            this->butOptions.draw(this->renderer);
            this->butQuitter.draw(this->renderer);

            break;

        case 1:
            drawText(this->renderer, "RTB Editor !", 80, this->winW/2, 50, 1, color);

            this->butRetourCreer.draw(this->renderer);
            break;

        case 20:{
            drawText(this->renderer, "RTB Editor !", 80, this->winW/2, 10, 1, color);
            drawText(this->renderer, "Options graphique", 50, this->winW/2, 100, 1, color);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75 + this->spacingWithScreen, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawGraphicOptions();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 23:{
            drawText(this->renderer, "RTB Editor !", 80, this->winW/2, 10, 1, color);
            drawText(this->renderer, "Credit", 50, this->winW/2, 100, 1, color);
            SDL_SetRenderDrawColor(this->renderer, 150, 150, 150, 100);
            SDL_Rect rect = {this->spacingWithScreen + this->borderSize, 75*2 + this->spacingWithScreen - this->borderSize, 250-this->borderSize*2, 75-this->borderSize*2};
            SDL_RenderFillRect(this->renderer, &rect);
            this->drawBaseOptions();

            this->drawCredit();

            this->butRetourOptions.draw(this->renderer);
            break;}

        case 3:
            drawText(this->renderer, "RTB Editor !", 80, this->winW/2, 50, 1, color);

            this->inputNewName.draw(this->renderer);
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
    drawText(this->renderer, "Options", 40, x+width/2+this->spacingWithScreen+this->borderSize, y+ height/6 +this->spacingWithScreen+this->borderSize, 1, color);

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
    drawText(this->renderer, "Resolution de l'ecran :", 30, this->winW/2 - 200, 250, 0, color);
    bool changeChoix = this->butChoixRes.draw(this->renderer);

    if (changeChoix){
        this->setScreenSize();
    }

    //Pleins écran
    drawText(this->renderer, "Plein ecran :", 30, this->winW/2 - 200, 330, 0, color);
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
    this->butRetourCreer.setX(this->winW/2 - 100);
    this->butRetourCreer.setY(this->winH-50 - 100);

    // Chargement
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
    myfile.open ("../data/saves/options.json"); // Ouverture du fichier

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
    std::ifstream myfile ("../data/saves/options.json");// Ouverture du fichier
    myfile >> json;

    this->butChoixRes.setValue(json["resolution"].asString());
    this->winW = json["winW"].asInt();
    this->winH = json["winH"].asInt();
    this->fullScreen.setActive(json["fullscreen"].asBool());
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
    return this->continuer;
}


int Menu::getWinWidth() {
    return this->winW;
}


int Menu::getWinHeight() {
    return this->winH;
}