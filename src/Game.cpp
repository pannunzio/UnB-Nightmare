/*
 * game.cpp
 *
 *  Created on: 12 de mar de 2016
 *      Author: Caio
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>

#include "Game.h"
#include "State.h"
#include "Vec2.h"
#include "TileSet.h"
#include "Resources.h"
#include "InputManager.h"
#include "Rect.h"
#include "TitleState.h"
using namespace std;





#include <cstdlib>
#include <ctime>
Game* Game::instance = nullptr;



Game::Game(string title, int width, int height){
	srand(time(NULL));
	dt =0;
	frameStart=0;

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) !=0)
		std::cout << "Error ao iniciar sdl:  " << SDL_GetError() << std::endl;
	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
		std::cout << "Error ao iniciar img" << SDL_GetError() << std::endl;
	if(Mix_Init(MIX_INIT_OGG) != (MIX_INIT_OGG))
		std::cout << "Error ao iniciar mixer" << SDL_GetError() << std::endl;
	if(TTF_Init()!=0)
			std::cout << "Error ao iniciar mixer" << SDL_GetError() << std::endl;

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);

	window = SDL_CreateWindow(
	    (const char*)title.c_str(),            //    const char* title
	    SDL_WINDOWPOS_CENTERED,               //    posiçao x inicial
	    SDL_WINDOWPOS_CENTERED, 			 //    poisiçao y inicial
	    width,                  		    //    largura
	    height,                 	       //    altura
	    0         	      //   window options
	  );
	if(!window)
		cout << "falha ao criar janela" << SDL_GetError() << endl;

	//**********************Janela criada*****************************************//
	// criando o renderer
	renderer = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED
		);
	if(!renderer)
		cout << "falha ao criar renderer:  " << SDL_GetError() << endl;
	//**********************Renderer criado*****************************************//
	storedState = nullptr;
	instance = this;
	std::cout << "Game built" << std::endl;
}

Game::~Game(){
	if(storedState)
		storedState = nullptr;
	while(!stateStack.empty())
		stateStack.pop();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	cout << "game destroyed" << endl;
}
void Game::Push(State* state){
	storedState = state;
	stateStack.emplace(state);
}

State& Game::GetCurrentState(){
	return *storedState;
}

SDL_Window* Game::GetWindow(){
	return window;
}
SDL_Renderer* Game::GetRenderer(){
	return renderer;
}

Game& Game::GetInstance(){
		return *instance;
	};





void Game::Run(){


	Push(new TitleState);
	// enquanto nao clicka fechar, continuar no loop
	while(!stateStack.top()->QuitRequested() && !stateStack.empty()){

		CalculateDeltaTime();
		frameStart = SDL_GetTicks();
		InputManager::GetInstance().Update();
		if(stateStack.top()->PopRequested()){
					stateStack.pop();
		}
		stateStack.top()->Update(dt);
		stateStack.top()->Render();


		//Clear screen
		SDL_RenderPresent(renderer); // força renderer tudo dnv
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
	this->dt = (SDL_GetTicks() - frameStart)/1000.0 ;
}








