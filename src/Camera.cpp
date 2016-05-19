/*
 * Camera.cpp
 *
 *  Created on: 25 de mar de 2016
 *      Author: Caio
 */

#include "Camera.h"
#include "InputManager.h"
#include "Player.h"
GameObject* Camera::focus = nullptr;;
Vec2 Camera::pos = Vec2(0,0);
Vec2 Camera::speed = Vec2(5,5);

#define CAMERA_MAXSPEED 5

Camera::Camera() {
	focus = nullptr;

}

Camera::~Camera() {

}


void Camera::Follow(GameObject* newFocus){
	focus = newFocus;
}
void Camera::Unfollow(){
	focus = nullptr;
}
void Camera::Update(float dt){
	if(focus){
		if(focus->IsDead())
			focus = nullptr;
		pos.x = focus->box.x + focus->box.w/2 - 1024/2;
		pos.y = focus->box.y + focus->box.h/2 - 600/2;
		if(InputManager::GetInstance().IsKeyDown(SDLK_k))
					focus = nullptr;

	}
	if(!focus){
		if(Player::GetInstance().GetSpeed() <= CAMERA_MAXSPEED)
			pos.x = pos.x + speed.x*dt*100 ;//- 0.1*(Player::GetInstance().GetSpeed() - MAXSPEED)*speed.x*dt*100;
		if(Player::GetInstance().GetSpeed() > CAMERA_MAXSPEED){
			if(Player::GetInstance().IsRightPosition())
				pos.x = pos.x + Player::GetInstance().GetSpeed()*dt*100 ;
			else
				pos.x = pos.x + speed.x*dt*100;

		}

	}
}
