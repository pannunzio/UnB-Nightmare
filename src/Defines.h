#ifndef DEFINES_H
#define DEFINES_H

#include <string>
#include <iostream>
#include "SDL.h"

//declarar todos os Usings mais usados aqui para nao ficar usando std::blablabla all the time
using std::string;
using std::cout;
using std::endl;

#define SCREEN_NAME string "UnB Nightmare"
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 1024

#define COLOR_BLACK SDL_Color{0, 0, 0}
#define COLOR_WHITE SDL_Color{255, 255, 255}

#define PLAYER_NORMAL_SPEED 5
#define PLAYER_SKATE_SPEED 7
#define PLAYER_NORMAL_ACCELERATION 1.5
#define PLAYER_DISTANCE_TO_CAMERA 200

#define TILE_WIDTH 256
#define TILE_HEIGHT 256

#define CAMERA_NORMAL_SPEED 5

#define BULLET_MAX_DISTANCE 500


//acrescentar mais aa medida q for usando

#endif
