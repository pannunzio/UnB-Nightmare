#include "Game.h"
#include "Defines.h"

int main(int argv, char** argc) {
	Game* game = new Game(SCREEN_NAME, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->Run();

    return 0;
}
