/*
 * Player.cpp
 *
 *  Created on: 18 de mai de 2016
 *      Author: apoio
 */

#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include <cstdlib>


Player* Player::player = nullptr;

#define MAXSPEED 5
#define DISTANCE_CAMERA 150

Player::Player() : sp("img/playerRunning.png", 4, 0.1){
	subLayer = 2;
	sp.SetScaleX(0.1);
	sp.SetScaleY(0.1);
	box.Centralize(50,300,sp.GetWidth(),sp.GetHeight());
	speed = MAXSPEED;
	acceleration = 1.5;
	isRightPosition = false;
	powerUp = NONE;
	targetSpeed = MAXSPEED;
	player = this;

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

Player& Player::GetInstance(){
	return *player;
}
float Player::GetSpeed(){
	return speed;
}

void Player::Update(float dt){
	std::cout << " box.x player: " << box.x << " camera pos: " << Camera::pos.x << std::endl;
	if(box.x - Camera::pos.x > DISTANCE_CAMERA)
		isRightPosition = true;
	else
		isRightPosition = false;


	//movimento de sublayer
	sp.Update(dt);
	if(InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
		if(subLayer <=2){
			subLayer++;
			box.y = box.y - 60;
		}
	}
	if(InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
		if(subLayer >=2){
			subLayer--;
			box.y = box.y + 60;
		}
	}

	if(!IsTargetSpeed(targetSpeed)){
		if(targetSpeed > speed)
			speed = speed + acceleration*dt;

		if(targetSpeed < speed)
			speed = speed - acceleration*dt;
	}

	//exemplo de pegou power up
	if(InputManager::GetInstance().KeyPress(SDLK_l))
		targetSpeed = 7.5;
	// exemplo de diminuir velocidade
	if(InputManager::GetInstance().KeyPress(SDLK_j))
		targetSpeed =4.5;
	// exemplo de velocidade voltou ao normal
	if(InputManager::GetInstance().KeyPress(SDLK_k))
		targetSpeed =5;

	//correndo
	box.x = box.x + speed*dt*100;

}
void Player::Render(){
	sp.Render((int)(box.x - Camera::pos.x), (int)(box.y - Camera::pos.y));
}
bool Player::IsDead(){
	return false; // retornar true se tiver camera passou, ou se o tempo acabou
	//isso pode ser feito pelo state data.

}
bool Player::Is(std::string type){
	return (type == "Player");

}
void Player::NotifyCollision(GameObject* other){

}
bool Player::IsTargetSpeed(float targetSpeed){
	if(targetSpeed <=0) // se algo a levar para tras
		speed = targetSpeed;
	if(abs(speed - targetSpeed) <= 0.005)
		return true;
	return false;
}

float Player::GetAcceleration(){
	return acceleration;
}
void Player::SetAcceleration(float acceleration){
	this->acceleration = acceleration;
}

bool Player::IsRightPosition(){
	return isRightPosition;
}
