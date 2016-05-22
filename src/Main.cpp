/*
 * Main.cpp
 *
 *  Created on: 15 de mai de 2016
 *      Author: Caio
 */

#include "Game.h"
#include "Defines.h"
int main(int argv, char** argc) {
	Game* game = new Game("Caio Oliveira- 140176713", SCREEN_WIDTH, SCREEN_HEIGHT);
	game->Run();

    return 0;
}
