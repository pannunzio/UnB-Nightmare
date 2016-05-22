/*
 * Camera.cpp
 *
 *  Created on: 25 de mar de 2016
 *      Author: Caio
 */
#include "Defines.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"


Vec2 Camera::pos = Vec2(0,0);
Vec2 Camera::speed = Vec2(CAMERA_NORMAL_SPEED,2);

int Camera::layer = 2;



Camera::Camera() {

}

Camera::~Camera() {

}



void Camera::Update(float dt){

		if(Player::player->GetSpeed() <= CAMERA_NORMAL_SPEED)
			pos.x = pos.x + speed.x*dt*100 ;//- 0.1*(Player::GetInstance().GetSpeed() - MAXSPEED)*speed.x*dt*100;
		if(Player::player->GetSpeed() > CAMERA_NORMAL_SPEED){
			if(Player::player->IsRightPosition())
				pos.x = pos.x + Player::player->GetSpeed()*dt*100 ;
			else
				pos.x = pos.x + speed.x*dt*100;
		}
		layer = Player::player->layer;


		// mudança de local
		// camera
		if(layer == 3)
			if(pos.y > 0)
				pos.y = pos.y - speed.y*dt*100;
		if(layer == 2 )
			if(pos.y > 220)
			pos.y = pos.y - speed.y*dt*100;
		if(layer == 2 )
			if(pos.y < 220)
			pos.y = pos.y + speed.y*dt*100;
		if(layer == 1)
			if(pos.y < 480)
				pos.y = pos.y + speed.y*dt*100;

}
