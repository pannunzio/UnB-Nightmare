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

Agua::Agua(int layer, int subLayer) : sp("img/agua.png", 2,0.2){
	this->isDead = false;
	this->speed = 1;
	this->layer = layer;
	this->subLayer = subLayer;

	this->box.x = Player::player->box.x + 1200;

	if(this->layer == LAYER_TOP)
        this->box.y = ITEM_HEIGHT_L3;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = ITEM_HEIGHT_L2;

    if(this->layer == LAYER_BOTTON)
        this->box.y = ITEM_HEIGHT_L1;

    this->box.y += sp.GetHeight();
	this->box.y -= (this->subLayer - 3) * 26 - 200;

}

Agua::~Agua(){
}

void Agua::Update(float dt){

	this->timer.Update(dt);

	this->sp.Update(dt);
	this->box.x += this->speed * dt * 100;

	if(this->speed == PLAYER_NORMAL_SPEED){
		this->deadTimer.Update(dt);
		this->box.y += 1 * dt * 100;
		this->deadTimer.Update(dt);
	}
    if(this->box.x - Camera::pos.x <= 0){
    	this->speed = PLAYER_NORMAL_SPEED;
    }

	if(this->deadTimer.Get() > 5)
		this->isDead = true;
}

void Agua::Render(){
	//sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
	this->sp.Render(this->box.x, this->box.y - Camera::pos.y);
}

bool Agua::IsDead(){
	return this->isDead;
}

void Agua::NotifyCollision(GameObject* other){

}

bool Agua::Is(std::string type){
	return (type == "Agua");
}

int Agua::GetLayer(){
    return this->layer;
}

int Agua::GetSublayer(){
    return this->subLayer;
}
