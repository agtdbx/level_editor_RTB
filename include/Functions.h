//
// Created by auguste on 31/01/2022.
//

#ifndef RTB_FUNCTIONS_H
#define RTB_FUNCTIONS_H

#include <SDL2/SDL.h>

void drawText(SDL_Renderer *renderer , char *text, int textSize, int x, int y, int alignement, SDL_Color color);

void drawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);

char *append_char ( const char *s, const char c );

#endif //RTB_FUNCTIONS_H
