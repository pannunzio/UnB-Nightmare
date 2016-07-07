#ifndef DEFINES_H
#define DEFINES_H

#include <string>
#include <iostream>
#include "SDL.h"

//declarar todos os Usings mais usados aqui para nao ficar usando std::blablabla all the time
using std::string;
using std::cout;
using std::endl;

#define SCREEN_NAME "UnB Nightmare"
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 1024

#define COLOR_BLACK SDL_Color{0, 0, 0}
#define COLOR_WHITE SDL_Color{255, 255, 255}

#define PLAYER_SLOW_SPEED 4
#define PLAYER_NORMAL_SPEED 5
#define PLAYER_SKATE_SPEED 7
#define PLAYER_NORMAL_ACCELERATION 1.5
#define PLAYER_DISTANCE_TO_CAMERA 200

#define TILESET_WIDTH 632
#define TILESET_HEIGHT 360

#define CAMERA_NORMAL_SPEED 5

#define BULLET_MAX_DISTANCE 1000
#define CACAPOMBO_MAX_DISTANCE 100

#define LAYER_TOP 3
#define LAYER_MIDDLE 2
#define LAYER_BOTTON 1

#define SUBLAYER_TOP 3
#define SUBLAYER_MIDDLE 2
#define SUBLAYER_BOTTON 1

//RENDERIZACAO DOS LAYERS


#define RENDER_HEIGHT_33
#define RENDER_HEIGHT_32
#define RENDER_HEIGHT_31 265

#define RENDER_HEIGHT_23 495
#define RENDER_HEIGHT_22
#define RENDER_HEIGHT_21 550


#define RENDER_HEIGHT_13 740
#define RENDER_HEIGHT_12
#define RENDER_HEIGHT_11

#define TITLE_MAX_OPTIONS 2
#define TITLE_MIN_OPTIONS 1

#define END_MAX_OPTIONS 2
#define END_MIN_OPTIONS 1

#define ITEM_HEIGHT_L3 222
#define ITEM_HEIGHT_L2 495
#define ITEM_HEIGHT_L1 765



//acrescentar mais aa medida q for usando

#endif
