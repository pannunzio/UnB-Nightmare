/*
 * Obstacle.cpp
 *
 *  Created on: 13 de jun de 2016
 *      Author: Caio
 */

#include "Obstacle.h"
#include "Camera.h"
#include "Defines.h"
#include "StageState.h"

Obstacle::Obstacle(int speed, float spawnRate,  bool canBlock, std::string obstacleName, int frameCount, float frameTime)
: sp(obstacleName,frameCount,frameTime) {
	this->speed = speed;
	this->spawnRate = spawnRate;
	this->obstacleName = obstacleName;
	this->canBlock = canBlock;
	layer = rand()%3 + 1;
	subLayer = rand()%3 + 1;

}

bool Obstacle::IsDead(){
	return false;
}
void Obstacle::Update(float dt){
	cooldownTimer.Update(dt);
	sp.Update(dt);
	int spawn = 100;
	if(cooldownTimer.Get() > 3) {// cada 3 segundos talvez spawna dnv
		spawn = rand()%100 +1;
	}
	if(spawn <= spawnRate*100){
		// ou seja, vai dar respawn se passar no teste  //
		box.x = Player::player->box.x + 1200;			//
	    if(layer == LAYER_TOP)							//
	        box.y=ITEM_HEIGHT_L3;						//
	    if(layer == LAYER_MIDDLE)						//
	        box.y=ITEM_HEIGHT_L2;						//
	    if(layer == LAYER_BOTTON)						//
	        box.y=ITEM_HEIGHT_L1;						//
	    												//
	    box.y = box.y - (this->subLayer - 3)*20;		//
	    ///////////////////////////////////////////////////
		Game::GetInstance().GetCurrentState().AddObject(this);
		spawn = 100;
		cooldownTimer.Restart();
	}

}
void Obstacle::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
}
bool Obstacle::Is(std::string type){
	return (type == obstacleName);
}
void Obstacle::NotifyCollision(GameObject* other){

}
