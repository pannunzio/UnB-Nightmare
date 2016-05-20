/*
 * Bullet.cpp
 *
 *  Created on: 31 de mar de 2016
 *      Author: Caio
 */

#include "Bullet.h"
#include "Camera.h"
#include "Game.h"


void Bullet::NotifyCollision(GameObject* other){
	if(other->Is("Penguins") && targetsPlayer)
		distanceLeft = 0;
	if(other->Is("Alien")&& !targetsPlayer)
		distanceLeft = 0;

}

bool Bullet::Is(std::string type){
	return(type == "Bullet");
}

Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance, string sprite, int frameCount
		,float frameTime, bool targetsPlayer) : sp(sprite,frameCount,frameTime){
	this->targetsPlayer = targetsPlayer;
	box.Centralize(x,y,sp.GetWidth(),sp.GetHeight());
	distanceLeft = maxDistance;
	rotation = angle;
	this->speed.x =  cos(angle*M_PI/180.0)*speed; // graus
	this->speed.y =  sin(angle*M_PI/180.0)*speed;

}




Bullet::~Bullet() {

}


bool Bullet::IsDead(){
	if(distanceLeft <= 0 )
		return true;
	return false;
}
void Bullet::Update(float dt){
	sp.Update(dt);
	// velocidades menor q 1 sao consideradas como 0
	Vec2 mover(speed.x*dt,speed.y*dt);
	//box.x += mover.x;
	//box.y += mover.y;
	box = box + mover;
	distanceLeft-= mover.Magnitude();
}
void Bullet::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y,rotation);
//	SDL_RenderDrawLine(Game::GetInstance().GetRenderer(),box.x -Camera::pos.x,
//																box.y - Camera::pos.y,
//																box.x + box.w - Camera::pos.x,
//																box.h + box.y - Camera::pos.y);

}
