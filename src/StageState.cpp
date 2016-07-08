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
#include "Pombo.h"
#include "Agua.h"

#include "MapActionList.h"



using std::string;
using std::cout;
using std::endl;

//**********************************************************************//
//Fun��o: StageState::Update()**********************************************//
//Retorno: void*******************************************************//
//Parametros: void***************************************************//
//Descri��o: atualizacao do state no game loop**********************//
//*****************************************************************//
void StageState::Update(float dt){

    if(!Player::player){
        cout<<"LOSER"<<endl;
        mapActionList.mapActions.clear();
        objectArray.clear();
    	Pause();
    	stateData.playerVictory = false;
    	popRequested = true;

    	Game::GetInstance().Push(new EndState(stateData));
    	return;
    }

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
            if((objectArray[i]->layer == objectArray[j]->layer) && (objectArray[i]->subLayer == objectArray[j]->subLayer)){
                if(j!=i && (Collision::IsColliding(objectArray[i]->box,objectArray[j]->box,
                                            objectArray[i]->rotation*M_PI/180,objectArray[j]->rotation*M_PI/180))){
                  objectArray[j]->NotifyCollision(objectArray[i].get());
                }
            }
		}

		if(objectArray[i]->IsDead()){
		   objectArray.erase (objectArray.begin() + i);
		   i--;
		}
    }

    for(int i = mapActionList.mapActions.size() - 1; i >= 0; i--) {
        if(Player::player != nullptr &&
           Collision::IsColliding(Player::player->box,
                                  mapActionList.mapActions[i].box,
                                  Player::player->rotation,
                                  mapActionList.mapActions[i].rotation)){

            Player::player->NotifyCollision(&mapActionList.mapActions[i]);
        }
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
        if(spawn == 0 && rand()%100 <= 80){
            if(rand()%3 ==1)
                 AddObject(new Item(Player::player->layer, rand()%3+1, "COFFEE"));
            else if(rand()%3 ==2)
                 AddObject(new Item(Player::player->layer, rand()%3+1, "SKATE"));
            else
                 AddObject(new Item(Player::player->layer, rand()%3+1, "GGLIKO"));
        }
        spawn = 1;
    }
    else if(spawn!=0){
        spawn = 0;
    }


//	respawn das coisas

    if((1256*lixo)<Camera::pos.x){
            AddObjectStatic(new Obstacle(0, true,"lixeira", "img/lixeira.png", 1, 1, LAYER_TOP));
            AddObjectStatic(new Obstacle(0, true,"lixeira", "img/lixeira.png", 1, 1, LAYER_MIDDLE));
            AddObjectStatic(new Obstacle(0, true,"lixeira", "img/lixeira.png", 1, 1, LAYER_BOTTON));
            lixo++;
    }

    cooldownTimer.Update(dt);
    if(cooldownTimer.Get() > 0.3){ // repete a cada meio segundo
    	cooldownTimer.Restart();
    	if(rand()%1000 <= 8){
    		 AddObject(new Agua(LAYER_BOTTON,SUBLAYER_BOTTON));
    		 AddObject(new Agua(LAYER_BOTTON,SUBLAYER_MIDDLE));
    		 AddObject(new Agua(LAYER_BOTTON,SUBLAYER_TOP));
    	}
    	if(rand()%100 <= 3){  //3%
    			AddObjectStatic(new Obstacle(0, false,"cano", "img/cano.png", 6,0.2,LAYER_BOTTON, SUBLAYER_TOP));
    	    	}


    	if(rand()%100 <= 30){ // 50% chance de aparecer
        	AddObject(new Obstacle(rand()%3 - rand()%3, true,"menina", "img/menina.png", 6, 0.2));

    	}
    	if(rand()%100 <=5){
    		// manifestacao
    		cout << "create manifest" << endl;
    		AddObject(new Obstacle(2, true,"manifestacao", "img/manifest-block.png", 1,1,LAYER_MIDDLE, SUBLAYER_TOP));
    		AddObject(new Obstacle(2, true,"manifestacao", "img/manifest-block.png", 1,1,LAYER_MIDDLE, SUBLAYER_MIDDLE));
    		AddObject(new Obstacle(2, true,"manifestacao", "img/manifest-block.png", 1,1,LAYER_MIDDLE, SUBLAYER_BOTTON));
    	}
    	if(Player::player->layer ==  LAYER_TOP){
            if(rand()%100 < 5){
         AddObjectStatic(new Pombo(Player::player->box.x + 1000, ITEM_HEIGHT_L3, Player::player->subLayer));
            }
    	}
    }

//    if(Player::player->movementState == GOING_DOWN && Player::player->layer == LAYER_BOTTON){
//        music.Stop();
//        music.Open("audio/subsolo_main.ogg");
//    }
//
//    if(Player::player->movementState == GOING_UP && Player::player->layer == LAYER_MIDDLE){
//        music.Stop();
//        music.Open("audio/tematerreo_voltaterreo.ogg");
//    }
      if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
    	ChangeMusic();
      }
      if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
          	ChangeMusic();
      }
}


//**********************************************************************//
//Fun��o: StageState::Render************************************************//
//Retorno: void*******************************************************//
//Parametros: void***************************************************//
//Descri��o: renderiza tudo que ta no state*************************//
//*****************************************************************//
void StageState::Render(){
	//chamando o render de cada gameObject
	bg.Render(0,0);
	Camera::Update(Game::GetInstance().GetDeltaTime());
	tileMap.RenderLayer(0,Camera::pos.x,Camera::pos.y );
	//tileMap.Render(0,0);
	//removr quando tiver okay!
	for(unsigned int i = 0 ; i < mapActionList.mapActions.size(); i++) {
        mapActionList.mapActions[i].Render();
	}
	for(unsigned int i = 0 ; i < objectArray.size(); i++) {
		if(objectArray[i]->subLayer == 3)
            objectArray[i]->Render();
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
//Fun��o: CONSTRUTOR**************************************************//
//Retorno: N/A*******************************************************//
//Parametros: N/A***************************************************//
//Descri��o: constroi o state com o background*********************//
//****************************************************************//
StageState::StageState() : tileMap("map/tileMap.txt", tileSet),bg("img/cerrado.jpg"), music("audio/tematerreo_main.ogg"){
	Camera::pos = Vec2(0,280);
	popRequested = quitRequested = false; // iniciando o valor como falso
	//ChangeMusic();
	//music.Play(-1);
	music.SetVolume(100);
	tileSet = new TileSet(TILESET_WIDTH,TILESET_HEIGHT,"img/tileset.png");
	tileMap.SetTileSet(tileSet);
	AddObject(new Player(200,550));
	//AddObject(new Item(LAYER_MIDDLE, SUBLAYER_TOP, "COFFEE"));
    spawn = 0;
    lixo=0;
	this->clock = Clock();





	//esse 200 e o player position
	//talvez seja melhor fazer por colis�o mas no momento n�o rola
	this->mapLength = (tileMap.GetWidth()*TILESET_WIDTH) - 200;
	//objetors


}
//*********************************************************************//
//Fun��o: DESTRUTOR***************************************************//
//Retorno: N/A*******************************************************//
//Parametros: N/A***************************************************//
//Descri��o: destroi o state **************************************//
//****************************************************************//
StageState::~StageState(){
	// limpando o vector
	mapActionList.mapActions.clear();
	objectArray.clear();
	Player::player = nullptr;
	cout << "StageState destroyed" << endl;
}
//Add game object
void StageState::AddObject(GameObject* ptr){
	objectArray.emplace_back(ptr);
}

void StageState::AddObjectStatic(GameObject* ptr){
	objectArray.emplace(objectArray.begin() ,ptr);
}

void StageState::Resume(){
	music.Play(-1);

}
void StageState::Pause(){
	music.Stop();
}
void StageState::ChangeMusic(){
   // music.Stop();
  //  if(Player::player->layer == 3)
  //    music.Open("audio/tematerreo_main.ogg");
//    if(Player::player->layer == 2)
//      this->music = Music("audio/tematerreo_main.ogg");
//    if(Player::player->layer == 1)
//      this->music = Music("audio/subsoloLoop.ogg");
  //  music.Play(-1);

}

