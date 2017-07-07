#include "NonCollidingPerson.h"

NonCollidingPerson::NonCollidingPerson():Obstacle(){
    this->type = Type::PELADO;
    this->sp = Sprite("img/pelado.png", 6, 0.2);
	this->speed = -5;
	SetHeight();
	this->subLayer = 0;
}

NonCollidingPerson::~NonCollidingPerson(){
    this->spriteSound.Stop();
}

void NonCollidingPerson::Render(){
    this->sp.RenderFlipped(this->box.x - Camera::GetX(), this->box.y - Camera::GetY());
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
