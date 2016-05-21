/*
 * Player.cpp
 *
 *  Created on: 18 de mai de 2016
 *      Author: apoio
 */

#include "Game.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include <cstdlib>

#include "Bullet.h"

#include "Defines.h"

Player* Player::player = nullptr;


Player::Player() : sp("img/playerRunning.png", 6, 0.09){
	subLayer = 2;

	box.Centralize(50,300,sp.GetWidth(),sp.GetHeight());
	targetSpeed = speed = PLAYER_NORMAL_SPEED;
	acceleration = 1.5;
	isRightPosition = false;
	powerUp = NONE;
	player = this;

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}
// teste git
Player& Player::GetInstance(){
	return *player;
}
float Player::GetSpeed(){
	return speed;
}

void Player::Update(float dt){
	sp.Update(dt);
	Movement(); // faz os movimentos do input

	//colocando na posicao certa o player
	if(box.x - Camera::pos.x > PLAYER_DISTANCE_TO_CAMERA)
		isRightPosition = true;
	else
		isRightPosition = false;


	//ir acelerando até a velocidade
	if(!IsTargetSpeed(targetSpeed)){
		if(targetSpeed > speed)
			speed = speed + acceleration*dt;

		if(targetSpeed < speed)
			speed = speed - acceleration*dt;
	}

	//correndo
	box.x = box.x + speed*dt*100;

	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
		Shoot();
	}

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

void Player::Movement(){
	if(InputManager::GetInstance().KeyPress(SDLK_l))
		targetSpeed = 7.5;
	// exemplo de diminuir velocidade
	if(InputManager::GetInstance().KeyPress(SDLK_j))
		targetSpeed =4.5;
	// exemplo de velocidade voltou ao normal
	if(InputManager::GetInstance().KeyPress(SDLK_k))
		targetSpeed =5;


	//movimento de sublayer
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


}

void Player::Shoot(){
	Vec2 shootPos = box.CenterPos();
	Bullet* coffee = new Bullet(shootPos.x,shootPos.y,10,"img/coffee.png", 3, 0.3,false, "coffee");
	Game::GetInstance().GetCurrentState().AddObject(coffee);
}
