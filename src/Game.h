/*
 * game.h
 *
 *  Created on: 12 de mar de 2016
 *      Author: Caio
 */

#ifndef GAME_H_
#define GAME_H_

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "state.h"

#include <stack>

#include <ctime>
#include <cstdlib>



using namespace std;

class Game {
public:
	Game(string title,int gWidth, int gHeight); //
	~Game();

	static Game& GetInstance();
	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();

	State& GetCurrentState();

	void Push(State* state);

	void Run();

	float GetDeltaTime();
private:
	void CalculateDeltaTime();

	int frameStart;
	float dt;

	static Game* instance;

	State* storedState;
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::stack<std::unique_ptr<State>> stateStack;
};

#endif /* GAME_H_ */
