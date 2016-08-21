#include "State.h"
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"
#include<iostream>

//Construtor
State::State(){
	this->quitRequested = false;
	this->popRequested = false;
}

State::~State(){
	objectArray.clear();
}


void State::Update(float dt){
}

void State::Render(){
	Camera::Update(Game::GetInstance().GetDeltaTime());

	for(unsigned int i = 0 ; i < objectArray.size(); i++)
		objectArray[i]->Render();
}

//void State::Pause(){}

//void State::Resume(){}

bool State::QuitRequested(){
	return quitRequested;
}

bool State::PopRequested(){
	return popRequested;
}

//Add game object
void State::AddObject(GameObject* ptr){
	objectArray.emplace_back(ptr);
}

void State::UpdateArray(float dt){
	for(unsigned int i = 0; i < objectArray.size(); i++)
		objectArray[i]->Update(dt);
}

void State::RenderArray(){
	for(unsigned int i = 0; i < objectArray.size(); i++)
        objectArray[i]->Render();
}
