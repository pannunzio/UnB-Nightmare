#include <iostream>
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

StageState::StageState() : tileMap("map/tileMap.txt", tileSet), bg("img/cerrado.jpg"){

	Camera::pos = Vec2(0,280);

	this->popRequested = false;
	this->quitRequested = false; // iniciando o valor como falso

	this->tileSet = new TileSet(TILESET_WIDTH, TILESET_HEIGHT, "img/tileset.png");
	this->tileMap.SetTileSet(tileSet);

	AddObject(new Player(200, 550));

    this->spawn = 0;
    this->lixo = 0;
	this->clock = Clock();

	//esse 200 e o player position
	this->mapLength = ((tileMap.GetWidth()-3)*TILESET_WIDTH) - 200;
	//objetors
}

StageState::~StageState(){
	// limpando o vector
	this->mapActionList.mapActions.clear();
	objectArray.clear();
	Player::player = nullptr;
	cout << "StageState destroyed" << endl;
}

void StageState::Update(float dt){
    CheckEndOfGame();

    this->clock.Update(dt);

    UpdateObjectArray(dt);
    CheckMapActionsPosition(dt);

    this->cooldownTimer.Update(dt);
    SpawnNewItem();
    SpawnNewStaticObstacle();
    SpawnNewDynamicObstacle();
}

void StageState::Render(){
    Camera::Update(Game::GetInstance().GetDeltaTime());

	//chamando o render de cada gameObject
	this->bg.Render(0, 0);
	this->tileMap.RenderLayer(0, Camera::pos.x,Camera::pos.y);

    RenderSubLayer(3);
    RenderSubLayer(2);
    RenderSubLayer(1);

	this->clock.Render();
}

void StageState::Pause(){
}

void StageState::Resume(){
}

//Add game object
void StageState::AddObject(GameObject* ptr){
	objectArray.emplace_back(ptr);
}

void StageState::AddObjectStatic(GameObject* ptr){
	objectArray.emplace(objectArray.begin() ,ptr);
}

//verifica se o jogo acabou
void StageState::CheckEndOfGame(){
    //Se o player não existir, encerra o jogo
    if(!Player::player){
        this->mapActionList.mapActions.clear();
        objectArray.clear();
    	SetEndOfGame(false);
    	return;
    }

    //se o usuario solicitar o fim do jogo ele encerra também
    if(InputManager::GetInstance().QuitRequested())
		this->quitRequested = true;

	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY))
		SetEndOfGame(false);

	//testa se o tempo acabou
    if(this->clock.GetTime() < 0.5){
        SetEndOfGame(false);
    }

    if(Camera::pos.x > this->mapLength){
        SetEndOfGame(true);
    }
}

void StageState::SetEndOfGame(bool playerVictory){
    this->stateData.timeleft = clock.GetTime();
    this->stateData.playerVictory = playerVictory;
    this->popRequested =  true;
    Game::GetInstance().Push(new EndState(stateData));
}

//Atualiza o array de Objectos e confere quais objectos 'morreram'
void StageState::UpdateObjectArray(float dt){
    //obs: NAO USAR O UPDATE ARRAY DO STATE!!!!
    for(unsigned int i = 0 ; i < objectArray.size(); i++){
    	objectArray[i]->Update(dt);
    	//checando colisisao
		for(unsigned int j = 0; j < objectArray.size(); j++){
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
}

//Verifica se o Player está passando na frente de algum objeto de mapa como as escadas, por exemplo
void StageState::CheckMapActionsPosition(float dt){
    for(int i = mapActionList.mapActions.size() - 1; i >= 0; i--) {
        if(Player::player != nullptr &&
           Collision::IsColliding(Player::player->box,
                                  this->mapActionList.mapActions[i].box,
                                  Player::player->rotation,
                                  this->mapActionList.mapActions[i].rotation)){

            Player::player->NotifyCollision(&mapActionList.mapActions[i]);
        }
	}
}

void StageState::SpawnNewItem(){
    if(this->clock.GetSeconds1()%2 == 0){
        if(this->spawn == 0 && rand()%100 <= 80){
            if(rand()%3 ==1)
                 AddObject(new Item(Player::player->layer, rand()%3+1, "COFFEE"));
            else if(rand()%3 ==2)
                 AddObject(new Item(Player::player->layer, rand()%3+1, "SKATE"));
            else
                 AddObject(new Item(Player::player->layer, rand()%3+1, "GGLIKO"));
        }
        this->spawn = 1;
    }
    else if(this->spawn != 0){
        this->spawn = 0;
    }
}

void StageState::SpawnNewStaticObstacle(){
//	respawn das coisas

    if((1256 * this->lixo) < Camera::pos.x){
        AddObjectStatic(new Obstacle(0, true,"lixeira", "img/lixeira.png", 1, 1, LAYER_TOP));
        AddObjectStatic(new Obstacle(0, true,"lixeira", "img/lixeira.png", 1, 1, LAYER_MIDDLE));
        AddObjectStatic(new Obstacle(0, true,"lixeira", "img/lixeira.png", 1, 1, LAYER_BOTTON));
        this->lixo++;
    }

    if(rand()%5000 <= 3){  //3%
        AddObjectStatic(new Obstacle(0, false,"cano", "img/cano.png", 6,0.2,LAYER_BOTTON, SUBLAYER_TOP));
    }
}

void StageState::SpawnNewDynamicObstacle(){
    if(this->cooldownTimer.Get() > 0.3){ // repete a cada meio segundo
    	this->cooldownTimer.Restart();
    	if(rand()%1000 <= 43){
    		 AddObject(new Agua(LAYER_BOTTON,SUBLAYER_BOTTON));
    		 AddObject(new Agua(LAYER_BOTTON,SUBLAYER_MIDDLE));
    		 AddObject(new Agua(LAYER_BOTTON,SUBLAYER_TOP));
    	}

    	if(rand()%100 <= 30){
        	AddObject(new Obstacle(rand()%3 - rand()%3, true,"menina", "img/menina.png", 6, 0.2));
    	}

    	if(rand()%100 <= 5){
            AddObject(new Obstacle(-5, false,"pelado", "img/pelado.png", 6, 0.2));
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
}

void StageState::RenderSubLayer(int sublayer){
    for(unsigned int i = 0 ; i < objectArray.size(); i++) {
		if(objectArray[i]->subLayer == sublayer)
            objectArray[i]->Render();
	}
}
