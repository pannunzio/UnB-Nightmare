/*
 * Agua.cpp
 *
 *  Created on: 7 de jul de 2016
 *      Author: Caio
 */

#include "Agua.h"

#include "Obstacle.h"
#include "Camera.h"
#include "Defines.h"
#include "StageState.h"
#include "Game.h"
#include "Player.h"


//VER ISSO AQUI
//void Sprite::SetAlpha(){
//	// colocar codigo aqui pra o sprite fazer transparente
//	// e ai coloca o sp.SetAlpha na agua.
//
//}


Agua::Agua(int layer, int subLayer) : sp("img/agua.png", 3,0.2){
	this->isDead = false;
	speed =2;
	this->layer=  layer;
	this->subLayer = subLayer;
	std::cout << "agua construida" << std::endl;

	box.x = Player::player->box.x + 1200;
	if(layer == LAYER_TOP)
	        box.y=ITEM_HEIGHT_L3;
	    if(layer == LAYER_MIDDLE)
	        box.y=ITEM_HEIGHT_L2;
	    if(layer == LAYER_BOTTON)
	        box.y=ITEM_HEIGHT_L1;
    box.y = box.y + sp.GetHeight();
	box.y = box.y - (this->subLayer - 3)*26;

}
Agua::~Agua(){

}

bool Agua::IsDead(){
	return isDead;
}
void Agua::Update(float dt){
	timer.Update(dt);

	sp.Update(dt);
	box.x = box.x + speed*dt*100;

	if(speed == PLAYER_NORMAL_SPEED){
		deadTimer.Update(dt);
		box.y = box.y + 1*dt*100;
		deadTimer.Update(dt);
	}
    if(box.x - Camera::pos.x <= 0){
    	speed = PLAYER_NORMAL_SPEED;


    }
	if(deadTimer.Get() > 5)
		this->isDead = true;
}
void Agua::Render(){
	//sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
}
bool Agua::Is(std::string type){
	return (type == "Agua");
}
void Agua::NotifyCollision(GameObject* other){

}
