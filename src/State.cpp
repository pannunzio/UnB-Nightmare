/*
 * State.cpp
 *
 *  Created on: 12 de mar de 2016
 *      Author: Caio
 */


#include "State.h"
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"
#include<iostream>

using std::string;
using std::cout;
using std::endl;

bool State::PopRequested(){
	return popRequested;
}
bool State::QuitRequested(){
	return quitRequested;
}
void State::UpdateArray(float dt){
	for(unsigned int i = 0; i < objectArray.size(); i++)
		objectArray[i]->Update(dt);
}
void State::RenderArray(){
	for(unsigned int i = 0; i < objectArray.size(); i++)
			objectArray[i]->Render();

}

void State::Update(float dt){
}

void State::Render(){
	Camera::Update(Game::GetInstance().GetDeltaTime());
	for(unsigned int i = 0 ; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}

State::State(){
	quitRequested = false; // iniciando o valor como falso
	popRequested = false;
}
State::~State(){
	objectArray.clear();
}
//Add game object
void State::AddObject(GameObject* ptr){
	objectArray.emplace_back(ptr);
}

