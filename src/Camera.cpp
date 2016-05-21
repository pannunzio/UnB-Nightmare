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
Vec2 Camera::speed = Vec2(CAMERA_NORMAL_SPEED,CAMERA_NORMAL_SPEED);

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
		// essa checagem na verdade tem q ser feita pelo player, ou seja, if playerWentUp, playerWentDown
		if(layer == 3)
			pos.y = 0;
		if(layer == 2)
			pos.y = 220;
		if(layer == 1)
			pos.y = 480;




}
