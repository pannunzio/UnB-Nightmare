// * State.cpp
// *
// *  Created on: 12 de mar de 2016
// *      Author: Caio
// */

#include<iostream>


#include "StageState.h"
#include "Game.h"
#include "GameObject.h"

#include "InputManager.h"
#include "Camera.h"
#include "EndState.h"

#include "Player.h"

#include "Collision.h"

#include "Defines.h"
#include "Clock.h"

using std::string;
using std::cout;
using std::endl;

//**********************************************************************//
//Função: StageState::Update()**********************************************//
//Retorno: void*******************************************************//
//Parametros: void***************************************************//
//Descrição: atualizacao do state no game loop**********************//
//*****************************************************************//
void StageState::Update(float dt){
    this->clock.Update(dt);
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

    if(!Player::player){
    	Pause();
    	stateData.playerVictory = false;
    	Game::GetInstance().Push(new EndState(stateData));
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
	tileMap.RenderLayer(0,Camera::pos.x,Camera::pos.y );
	//tileMap.Render(0,0);
	for(unsigned int i = 0 ; i < objectArray.size(); i++) {
		// cout intuito de bebugar
		//std::cout << "Entered for StageState::Render" << std::endl;
		objectArray[i]->Render();
	}
	//tileMap.RenderLayer(1,Camera::pos.x,Camera::pos.y);
	this->clock.Render();
}


//*********************************************************************//
//Função: CONSTRUTOR**************************************************//
//Retorno: N/A*******************************************************//
//Parametros: N/A***************************************************//
//Descrição: constroi o state com o background*********************//
//****************************************************************//
StageState::StageState() : tileMap("map/tileMap.txt", tileSet),bg("img/ocean.jpg")/*, music("audio/subsoloLoop.ogg")*/{
	Camera::pos = Vec2(0,280);
	popRequested = quitRequested = false; // iniciando o valor como falso
//	music.Play(-1);
	tileSet = new TileSet(TILESET_WIDTH,TILESET_HEIGHT,"img/tileset.png");
	tileMap.SetTileSet(tileSet);
	AddObject(new Player(200,540));

	this->clock = Clock();
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
	Player::player = nullptr;
	cout << "StageState destroyed" << endl;
}
//Add game object
void StageState::AddObject(GameObject* ptr){
	objectArray.emplace_back(ptr);
}
void StageState::Resume(){
//	music.Play(-1);

}
void StageState::Pause(){
//	music.Stop();
}
