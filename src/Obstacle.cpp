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
#include "Game.h"
#include "Player.h"

Obstacle::Obstacle(int speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime)
{
	sp = Sprite(sprite,frameCount,frameTime);
	this->speed = speed;

	this->obstacleName = obstacleName;
	this->canBlock = canBlock;
	layer = rand()%3 + 1;
	subLayer = rand()%3 + 1;
	this->isDead = false;

	// ou seja, vai dar respawn se passar no teste  //
	box.x = Player::player->box.x + 1200;			//
    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;						//
    												//
    box.y = box.y - (this->subLayer - 3)*26;		//
    ///////////////////////////////////////////////////
}

Obstacle::~Obstacle(){

}

bool Obstacle::IsDead(){
	return this->isDead;
}
void Obstacle::Update(float dt){
	sp.Update(dt);

    if(box.x - Camera::pos.x +100< 0)
		this->isDead = true;
}
void Obstacle::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
}
bool Obstacle::Is(std::string type){
	return (type == obstacleName);
}
void Obstacle::NotifyCollision(GameObject* other){
    if(other->Is("Player") && other->subLayer == this->subLayer){
       // this->isDead = true;
    }
}
