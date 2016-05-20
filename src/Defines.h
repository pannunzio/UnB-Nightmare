#ifndef DEFINES_H
#define DEFINES_H

#include <string>
#include "SDL.h"

//declarar todos os Usings mais usados aqui para nao ficar usando std::blablabla all the time
using std::string;
using std::cout;
using std::endl;

#define SCREEN_NAME string "UnB Nightmare"
#define SCREEN_HEIGHT int 600
#define SCREEN_WIDTH int 1024

#define COLOR_BLACK SDL_Color{0, 0, 0}
#define COLOR_WHITE SDL_Color{255, 255, 255}

//acrescentar mais aa medida q for usando

#endif 