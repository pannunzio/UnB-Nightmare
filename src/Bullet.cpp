/*
 * Bullet.cpp
 *
 *  Created on: 31 de mar de 2016
 *      Author: Caio
 */

#include "Bullet.h"
#include "Camera.h"
#include "Game.h"
#include "Defines.h"
#include "Player.h"

void Bullet::NotifyCollision(GameObject* other){
	if(other->Is("Enemy")&& !targetsPlayer)
		distanceLeft = 0;

}

bool Bullet::Is(std::string type){
	return(type == this->type);
}

Bullet::Bullet(float x, float y,  float speed, string sprite, int frameCount,float frameTime, bool targetsPlayer, std::string type)
		: sp(sprite,frameCount,frameTime)
{
    this->layer = 2;
    this->subLayer = 2;
	this->type = type;
	this->speed = speed;
	this->targetsPlayer = targetsPlayer;
	box.Centralize(x,y,sp.GetWidth(),sp.GetHeight());
	distanceLeft = BULLET_MAX_DISTANCE;
}

Bullet::~Bullet() {

}

void Bullet::SetLayers(int layer, int subLayer){
    this->layer = layer;
    this->subLayer = subLayer;
}


bool Bullet::IsDead(){
	if(distanceLeft <= 0 )
		return true;
	return false;
}
void Bullet::Update(float dt){
	sp.Update(dt);
	box.x = box.x + speed*dt*100;
	distanceLeft-= speed*dt*100;
}
void Bullet::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y,rotation);
}
