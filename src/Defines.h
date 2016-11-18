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

#define LAYER_TOP 3
#define LAYER_MIDDLE 2
#define LAYER_BOTTON 1

#define SUBLAYER_TOP 3
#define SUBLAYER_MIDDLE 2
#define SUBLAYER_BOTTON 1

//RENDERIZACAO DOS LAYERS

#define LAYER_TOP_HEIGHT 200
#define LAYER_MIDDLE_HEIGHT 405
#define LAYER_BOTTON_HEIGHT 625
#define SUBLAYER_HEIGHT 10;

#endif
