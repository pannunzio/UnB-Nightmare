/*
 * State.cpp
 *
 *  Created on: 12 de mar de 2016
 *      Author: Caio
 */

#include<iostream>


#include "StageState.h"
#include "Game.h"
#include "GameObject.h"

#include "InputManager.h"
#include "Camera.h"
#include "EndState.h"

#include "Player.h"

#include "Collision.h"


#define TILESET_WIDTH 256
#define TILESET_HEIGHT 256


using namespace std;

//**********************************************************************//
//Função: StageState::Update()**********************************************//
//Retorno: void*******************************************************//
//Parametros: void***************************************************//
//Descrição: atualizacao do state no game loop**********************//
//*****************************************************************//
void StageState::Update(float dt){
	if(InputManager::GetInstance().QuitRequested())
		quitRequested = true;
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		popRequested = true;
		Pause();
	}
    for(unsigned int i = 0 ; i < objectArray.size(); i++){
    	objectArray[i]->Update(dt);
    	//checando colisisao
		for(unsigned int j = i + 1; j < objectArray.size(); j++){
			if (Collision::IsColliding(objectArray[i]->box,objectArray[j]->box,
										objectArray[i]->rotation*M_PI/180,objectArray[j]->rotation*M_PI/180)){
			  objectArray[i]->NotifyCollision(objectArray[j].get());
			  objectArray[j]->NotifyCollision(objectArray[i].get());
			}
		}
		if(objectArray[i]->IsDead()){
		   objectArray.erase (objectArray.begin() + i);
		   i--;
		}
    }


}


//**********************************************************************//
//Função: StageState::Render************************************************//
//Retorno: void*******************************************************//
//Parametros: void***************************************************//
//Descrição: renderiza tudo que ta no state*************************//
//*****************************************************************//
void StageState::Render(){
	//chamando o render de cada gameObject
	bg.Render(0,0);
	Camera::Update(Game::GetInstance().GetDeltaTime());
	tileMap.RenderLayer(0,Camera::pos.x,Camera::pos.y + 100);
	//tileMap.Render(0,0);
	for(unsigned int i = 0 ; i < objectArray.size(); i++) {
		// cout intuito de bebugar
		//std::cout << "Entered for StageState::Render" << std::endl;
		objectArray[i]->Render();
	}
	//tileMap.RenderLayer(1,Camera::pos.x,Camera::pos.y);
}


//*********************************************************************//
//Função: CONSTRUTOR**************************************************//
//Retorno: N/A*******************************************************//
//Parametros: N/A***************************************************//
//Descrição: constroi o state com o background*********************//
//****************************************************************//
StageState::StageState() : tileMap("map/tileMap.txt", tileSet),bg("img/ocean.jpg"), music("audio/subsoloLoop.ogg"){
	popRequested = quitRequested = false; // iniciando o valor como falso
	music.Play(-1);
	stateData.playerVictory = false;
	tileSet = new TileSet(TILESET_WIDTH,TILESET_HEIGHT,"img/tileset2.png");
	tileMap.SetTileSet(tileSet);
	AddObject(new Player());
	//objetors
}
//*********************************************************************//
//Função: DESTRUTOR***************************************************//
//Retorno: N/A*******************************************************//
//Parametros: N/A***************************************************//
//Descrição: destroi o state **************************************//
//****************************************************************//
StageState::~StageState(){
	// limpando o vector
	objectArray.clear();
	cout << "StageState destroyed" << endl;
}
//Add game object
void StageState::AddObject(GameObject* ptr){
	objectArray.emplace_back(ptr);
}
void StageState::Resume(){
	music.Play(-1);

}
void StageState::Pause(){
	music.Stop();
}

