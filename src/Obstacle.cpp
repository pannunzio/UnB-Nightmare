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
// obstaculos normais
Obstacle::Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime)
{
	sp = Sprite(sprite,frameCount,frameTime);
	this->speed = speed;
	speed = speed + rand()%10/10;
	this->obstacleName = obstacleName;
	this->canBlock = canBlock;
	this->isDead = false;

	layer = rand()%3 + 1;
	subLayer = rand()%3 + 1;

	// ou seja, vai dar respawn se passar no teste  //
	box.x = Player::player->box.x + 1200;			//
    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;

    if(obstacleName == "lixeira"){
        subLayer = 3;
        box.y += 15;
    }
    												//
    box.y = box.y - (this->subLayer - 3)*26;		//
    ///////////////////////////////////////////////////
}

Obstacle::Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime,
		int layer, int subLayer)
{
	sp = Sprite(sprite,frameCount,frameTime);
	this->speed = speed;
	if(speed!=0)
		speed = speed + rand()%10/10;
	this->obstacleName = obstacleName;
	this->canBlock = canBlock;
	this->isDead = false;

	this->layer = layer;
	this->subLayer = subLayer;


	// ou seja, vai dar respawn se passar no teste  //
	box.x = Player::player->box.x + 1200;			//
    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;
    // tem q ser tipo assim os outros tbm, dps alguem arruma ai
    box.y = box.y + sp.GetHeight();	 				//
    												//
    box.y = box.y - (this->subLayer - 3)*26;		//
    ///////////////////////////////////////////////////

    // consertar isso para pegar geral
    if(obstacleName == "manifestacao" && subLayer == SUBLAYER_BOTTON){
    	if(layer == LAYER_MIDDLE)
    		box.y = box.y - 120;
    	sp = Sprite("img/manifest.png", 6, 0.2);

    }

    if(obstacleName == "pombo"){
        box.y -= 200;
    }
}





Obstacle::~Obstacle(){

}

bool Obstacle::IsDead(){
	return this->isDead;
}
void Obstacle::Update(float dt){
	sp.Update(dt);
	box.x = box.x + speed*dt*100;

    if(box.x - Camera::pos.x +sp.GetWidth()< 0)
		this->isDead = true;
}
void Obstacle::Render(){
	if(speed>=0)
		sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
	else
		sp.RenderFlipped(box.x - Camera::pos.x, box.y - Camera::pos.y);

}
bool Obstacle::Is(std::string type){
	return (type == obstacleName);
}
void Obstacle::NotifyCollision(GameObject* other){
    if(other->Is("Coffee")){
    	speed = 8;
    	std::cout << "teste cafe" << std::endl;
    }
}
