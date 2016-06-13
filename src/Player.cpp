#include "Game.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Text.h"
#include <cstdlib>
#include <sstream>

#include "Bullet.h"

#include "Defines.h"

Player* Player::player = nullptr;
int Player::coffee_ammo = 3;


Player::Player(float x, float y) : sp("img/playerRunning.png", 6, 0.09){
	subLayer = SUBLAYER_MIDDLE;
	layer = LAYER_MIDDLE;
	box.Centralize(x,y,sp.GetWidth(),sp.GetHeight());
	targetSpeed = speed = PLAYER_NORMAL_SPEED;
	acceleration = 1.5;
	isRightPosition = false;
	powerUp = NONE;
	player = this;

	std::cout << "Player Construido" << std::endl;

}

Player::~Player() {
	player = nullptr;
}


float Player::GetSpeed(){
	return speed;
}

void Player::Update(float dt){
//	clock.Update(dt);
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


	//cafe

	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
		Shoot();
	}

}
void Player::Render(){
	sp.Render((int)(box.x - Camera::pos.x), (int)(box.y - Camera::pos.y));
	RenderHud();
}
bool Player::IsDead(){
	// camera passou player
	if(Camera::pos.x > pos.x + sp.GetWidth()){
		player = nullptr;
		return true;
	}
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
	pos = box.CenterPos();

	if(subLayer > 3)
		subLayer = 3;
	if(subLayer < 1)
		subLayer = 1;

	if(InputManager::GetInstance().KeyPress(SDLK_w)){
		std::cout << "DEBUG\n" << std::endl;
		std::cout << "-------------PLayer---------------------"  << std::endl;
		std::cout << "Layer: " << layer  << std::endl;
		std::cout << "suLayer: " << subLayer << std::endl;
	}

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
			box.y = box.y - 20;
		}
	}
	if(InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
		if(subLayer >=2){
			subLayer--;
			box.y = box.y + 20;
		}
	}

	if(subLayer == SUBLAYER_TOP)
		if(layer == LAYER_MIDDLE || layer == LAYER_BOTTON)
			if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
				layer++;

//				box.y = box.y - 100;
				subLayer = SUBLAYER_BOTTON;
				if(layer == LAYER_MIDDLE)
					box.y = RENDER_HEIGHT_21;
				if(layer == LAYER_TOP)
					box.y = RENDER_HEIGHT_31;

			}

	if(subLayer == SUBLAYER_BOTTON)
		if(layer == LAYER_TOP || layer == LAYER_MIDDLE)
			if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
				layer--;
				subLayer = SUBLAYER_TOP;
				if(layer == LAYER_MIDDLE)
					box.y = RENDER_HEIGHT_23;
				if(layer == LAYER_BOTTON)
					box.y = RENDER_HEIGHT_13;

			}

}

void Player::Shoot(){
	Vec2 shootPos = box.CenterPos();
	if(coffee_ammo>0){
		Bullet* coffee = new Bullet(shootPos.x,shootPos.y,10,"img/coffee.png", 3, 0.3,false, "coffee");
		Game::GetInstance().GetCurrentState().AddObject(coffee);
		coffee->SetLayers(layer,subLayer); // para renderizar corretamente
		coffee_ammo--;
	}
}

void Player::RenderHud(){
	//QUANDO ARRUMAR VAZAMENTO DE MEMORIA, DESCOMENTAR ISSO AKI

	//std::string hudString = "Coffee: " + to_string(coffee_ammo);
	//hud = Text("font/arial.ttf", 28, SOLID, hudString, TEXT_WHITE, 40,50 );
	//hud.Render(0,0);

}

