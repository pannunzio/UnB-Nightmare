#include "NonCollidingPerson.h"

NonCollidingPerson::NonCollidingPerson(){
    this->type = Type::PELADO;
    this->sp = Sprite("img/pelado.png", 6, 0.2);
	this->speed = -5;
	this->canBlock = false;
	this->isDead = false;
    this->layer = Player::GetInstance().GetLayer();
	this->subLayer = 0;

	this->spriteSound = Sound(-1);
//    this->captureSound = Sound(-1);

    this->box.x = Player::GetInstance().GetX() + 1200;

    if(this->layer == LAYER_TOP)
        this->box.y = LAYER_TOP_HEIGHT;

    if(this->layer == LAYER_MIDDLE)
        box.y = LAYER_MIDDLE_HEIGHT;

    if(this->layer == LAYER_BOTTON)
        this->box.y = LAYER_BOTTON_HEIGHT;

    this->box.y += 65;
}

NonCollidingPerson::~NonCollidingPerson(){
    this->spriteSound.Stop();
}

void NonCollidingPerson::Render(){
    this->sp.RenderFlipped(this->box.x - Camera::GetX(), this->box.y - Camera::GetY() - 30);
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
    if(!Player::GetInstance().IsDead())
        return Player::GetInstance().GetSublayer();
    else
        return this->subLayer;
}
