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
#include "Item.h"
#include "Collision.h"

#include "Defines.h"
#include "Clock.h"

#include "Obstacle.h"

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
		for(unsigned int j = 0; j < objectArray.size(); j++){
            //std::cout << "obj1: " <<i<<" "<<objectArray[i]->box.x << "|||obj2:"<<j<<" "<<objectArray[j]->box.x << std::endl;
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
    	popRequested = true;
    	Game::GetInstance().Push(new EndState(stateData));
    }

    //testa se o tempo acabou
    if(clock.GetTime() < 0.5){
        Pause();
        stateData.playerVictory = false;
        stateData.timeleft = 0;
        popRequested = true;
        Game::GetInstance().Push(new EndState(stateData));
    }

    if(Camera::pos.x > this->mapLength){
        Pause();
        stateData.playerVictory = true;
        stateData.timeleft = clock.GetTime();
        popRequested =  true;
        Game::GetInstance().Push(new EndState(stateData));
    }
    if(clock.GetSeconds1()%2 == 0){
//        if(spawn==0)
//            std::cout<<clock.GetSeconds1()<<std::endl;
        if(spawn == 0 && rand()%100 <= 50)
            AddObject(new Item(Player::player->layer, rand()%3+1, "COFFEE"));
        spawn = 1;
    }
    else if(spawn!=0){
        spawn = 0;
    }

    // COOLDOWN TIMER DO CAIO, acho melhor q fazer tipo o de cima
    cooldownTimer.Update(dt);
    if(cooldownTimer.Get() > 0.5){ // repete a cada meio segundo
    	cooldownTimer.Restart();
    	if(rand()%100 <= 90) // 90% chance de aparecer
        	AddObject(new Obstacle(0, true,"obstacle1", "img/obstacle1.png", 1, 1));
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
		if(objectArray[i]->subLayer == 3)
            objectArray[i]->Render();
        if(objectArray[i]->Is("Item")){
            objectArray[i]->Render();
        }
	}
	for(unsigned int i = 0 ; i < objectArray.size(); i++) {
		if(objectArray[i]->subLayer == 2)
            objectArray[i]->Render();
	}
	for(unsigned int i = 0 ; i < objectArray.size(); i++) {
		if(objectArray[i]->subLayer == 1)
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
StageState::StageState() : tileMap("map/tileMap.txt", tileSet),bg("img/ocean.jpg"), music("audio/subsoloLoop.ogg"){
	Camera::pos = Vec2(0,280);
	popRequested = quitRequested = false; // iniciando o valor como falso
	music.Play(-1);
	tileSet = new TileSet(TILESET_WIDTH,TILESET_HEIGHT,"img/tileset.png");
	tileMap.SetTileSet(tileSet);
	AddObject(new Player(200,550));
	//AddObject(new Item(LAYER_MIDDLE, SUBLAYER_TOP, "COFFEE"));
    spawn=0;
	this->clock = Clock();

	//esse 200 e o player position
	//talvez seja melhor fazer por colisão mas no momento não rola
	this->mapLength = (tileMap.GetWidth()*TILESET_WIDTH) - 200;
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
	music.Play(-1);

}
void StageState::Pause(){
	music.Stop();
}
