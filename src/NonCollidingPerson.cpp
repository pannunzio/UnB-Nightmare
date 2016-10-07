#include "NonCollidingPerson.h"
#include "Camera.h"
#include "Player.h"

NonCollidingPerson::NonCollidingPerson(){
    this->type = Type::PELADO;
    this->sp = Sprite("img/pelado.png", 6, 0.2);
	this->speed = -5;
	this->canBlock = false;
	this->isDead = false;
	this->layer = Player::player->GetLayer();
	this->subLayer = 0;

	this->spriteSound = Sound(-1);
//    this->captureSound = Sound(-1);

	this->box.x = Player::player->box.x + 1200;

    if(this->layer == LAYER_TOP)
        this->box.y = OBST_HEIGHT_L3;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = OBST_HEIGHT_L2;

    if(this->layer == LAYER_BOTTON)
        this->box.y = OBST_HEIGHT_L1;

    this->box.y += 65;
}

NonCollidingPerson::~NonCollidingPerson(){
    this->spriteSound.Stop();
}

void NonCollidingPerson::Render(){
    this->sp.RenderFlipped(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 30);
}

void NonCollidingPerson::NotifyCollision(GameObject* other){
    //nao collide com nada por enquanto
}

bool NonCollidingPerson::Is(string type){
    return type == "NonColliding";
}

int NonCollidingPerson::GetLayer(){
    return this->layer;
}

int NonCollidingPerson::GetSublayer(){
    return this->subLayer;
}
