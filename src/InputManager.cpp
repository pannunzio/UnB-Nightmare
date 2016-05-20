/*
 * InputManager.cpp
 *
 *  Created on: 24 de mar de 2016
 *      Author: Caio
 */

#include "InputManager.h"
#include <iostream>
#include <SDL.h>
//***************************************************************//
//Função: InputManager::GetInstance()***************************//
//Retorno: InputManager&***************************************//
//Parametros: void********************************************//
//Descrição: faz o meyers singleton do input*****************//
//**********************************************************//
InputManager& InputManager::GetInstance(){ // precisa ser statico por conta do singleton
	static InputManager instance;
	return instance;
	// meyers singleton
};

//***************************************************//
//Função: CONSTRUTOR********************************//
//Retorno: N/A*************************************//
//Parametros: void********************************//
//Descrição: constroi o InputManager*************//
//**********************************************//
InputManager::InputManager() {
	for(int i = 0; i < 416 ; i++){
		keyState[i] = false;
		keyUpdate[i] = 0;
	}
	for(int i = 0; i < 6 ; i++){
		mouseUpdate[i] = 0;
		mouseState[i] = false;
	}
	quitRequested = false;
	updateCounter = 0;
	mouseX = 500;
	mouseY = 250;

}
//**********************************************************************//
//Função: InputManager::Update()***************************************//
//Retorno: void*******************************************************//
//Parametros: void***************************************************//
//Descrição: atualizacao do InputManager no game loop***************//
//*****************************************************************//
void InputManager::Update(){
	updateCounter++;
	SDL_Event event;
	quitRequested = false;
	while (SDL_PollEvent(&event)){
		SDL_GetMouseState(&mouseX, &mouseY); // pegando pos do mouse
//		quitRequested = false;


		if(SDL_QuitRequested())
			quitRequested = true;
		int tecla;
		if(event.key.keysym.sym >= 0x40000000 && event.key.keysym.sym <= 0x4000011A)
			tecla = event.key.keysym.sym - 0x3FFFFF81;
		else if(event.key.keysym.sym < 416)
			tecla = event.key.keysym.sym;
		else
			tecla = 0;

		if(event.type == SDL_KEYDOWN && event.key.repeat != 1){
			keyState[tecla] = true;
			keyUpdate[tecla] = updateCounter;
		}

		if(event.type == SDL_KEYUP && event.key.repeat != 1){
			keyState[tecla] = false;
			keyUpdate[tecla] = updateCounter;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		}

		if(event.type == SDL_MOUSEBUTTONUP){
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
		}

	}

}

//**********************************************************************//
//Função: InputManager::Verificacoes de teclas*************************//
//Retorno: void*******************************************************//
//Parametros: void***************************************************//
//Descrição: verificas se teclas estao apertadas ou soltas**********//
//*****************************************************************//
bool InputManager::IsKeyUp(int key){
	if(key >= 0x40000000 && key <= 0x4000011A)
		key-= 0x3FFFFF81;
	if(keyState[key] == false){
		return true;
	}
	return false;
}

bool InputManager::IsKeyDown(int key){
	if(key >= 0x40000000 && key <= 0x4000011A)
		key-= 0x3FFFFF81;
	if(keyState[key] == true)
		return true;
	return false;
}
bool InputManager::KeyRelease(int key){
	if(key >= 0x40000000 && key <= 0x4000011A)
		key-= 0x3FFFFF81;
	if(keyState[key] == false && keyUpdate[key] == updateCounter){
		return true;
	}
	return false;
}
bool InputManager::KeyPress(int key){
	if(key >= 0x40000000 && key <= 0x4000011A)
		key-= 0x3FFFFF81;
	if(keyState[key] == true && keyUpdate[key] == updateCounter){
		return true;
	}
	return false;
}

bool InputManager::IsMouseUp(int button){
	if(mouseState[button] == false)
		return true;
	return false;
}
bool InputManager::IsMouseDown(int button){
	if(mouseState[button] == true)
		return true;
	return false;
}
bool InputManager::MouseRelease(int button){
	if(mouseState[button] == false && mouseUpdate[button] == updateCounter){
		return true;
	}
	return false;
}

bool InputManager::MousePress(int button){
	if(mouseState[button] == true && mouseUpdate[button] == updateCounter){
		return true;
	}
	return false;
}


/**************Pega a posiçao do mouse******************/
int InputManager::GetMouseX(){
	return mouseX;
}
int InputManager::GetMouseY(){
	return mouseY;
}
/***************Retorna o quitRequested***************/
bool InputManager::QuitRequested(){
	return quitRequested;
}


InputManager::~InputManager() {
}

