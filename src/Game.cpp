#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>

#include "State.h"
#include "Vec2.h"
#include "TileSet.h"
#include "Resources.h"
#include "InputManager.h"
#include "Rect.h"
#include "TitleState.h"
#include "Defines.h"
#include <cstdlib>
#include <stdio.h>
#include <ctime>

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height){
	srand(time(NULL));
	this->dt = 0;
	this->frameStart = 0;

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) !=0)
		std::cout << "Error ao iniciar sdl:  " << SDL_GetError() << std::endl;

	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
		std::cout << "Error ao iniciar img: " << SDL_GetError() << std::endl;

	if(Mix_Init(MIX_INIT_OGG) != (MIX_INIT_OGG))
		std::cout << "Error ao iniciar mixer: " << SDL_GetError() << std::endl;

	if(TTF_Init()!=0)
			std::cout << "Error ao iniciar mixer: " << SDL_GetError() << std::endl;

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	window = SDL_CreateWindow((const char*)title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	if(!window)
		cout << "falha ao criar janela: " << SDL_GetError() << endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!renderer)
		cout << "falha ao criar renderer: " << SDL_GetError() << endl;

	this->storedState = nullptr;
	this->instance = this;
	std::cout << "Game built" << std::endl;

	SDL_version compiled;
    const SDL_version *linked;

    SDL_TTF_VERSION(&compiled);
    linked = TTF_Linked_Version();
    printf("We compiled against SDL version %d.%d.%d ...\n", compiled.major, compiled.minor, compiled.patch);
    printf("But we are linking against SDL version %d.%d.%d.\n", linked->major, linked->minor, linked->patch);

}

Game::~Game(){
	if(this->storedState)
		this->storedState = nullptr;

	while(!this->stateStack.empty())
		this->stateStack.pop();

	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	cout << "game destroyed" << endl;
}

Game& Game::GetInstance(){
    return *instance;
}

SDL_Renderer* Game::GetRenderer(){
	return this->renderer;
}

SDL_Window* Game::GetWindow(){
	return this->window;
}

State& Game::GetCurrentState(){
	return *this->stateStack.top();
}

void Game::Push(State* state){
    this->storedState = state;
}

void Game::Run(){
    int cont = 0;
    std::cout << cont << "  --  emplace and call begin -- " << std::endl;
	this->stateStack.emplace(new TitleState);
	this->stateStack.top()->LoadAssets();
    cont ++;

	while(!this->stateStack.top()->QuitRequested() && !this->stateStack.empty()){

		CalculateDeltaTime();
		this->frameStart = SDL_GetTicks();
		InputManager::GetInstance().Update();

		this->stateStack.top()->Update(dt);
		this->stateStack.top()->Render();

		if(this->stateStack.top()->QuitRequested())
			break;

		if(this->stateStack.top()->PopRequested())
			this->stateStack.pop();

		if(this->storedState!=nullptr){
            std::cout << cont << "  --  emplace and call begin -- " << std::endl;
			this->stateStack.emplace(storedState);
			this->storedState = nullptr;
			this->stateStack.top()->LoadAssets();
			cont ++;
		}

		//Clear screen
		SDL_RenderPresent(this->renderer); // força renderer tudo dnv
		//SDL_Delay(33); // isso vai dar aproximadamente 33 frames/s
	}

	std::cout << "saiu no game run" << std::endl;
	Resources::ClearImages();
	delete instance;
}

float Game::GetDeltaTime(){
	return this->dt;
}

void Game::CalculateDeltaTime(){
	this->dt = (SDL_GetTicks() - this->frameStart) / 1000.0;
}
