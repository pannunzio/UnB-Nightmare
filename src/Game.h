#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <stack>
#include <ctime>
#include <cstdlib>

#include "State.h"

using std::string;
using std::cout;
using std::endl;

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
