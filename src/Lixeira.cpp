#include "Lixeira.h"

Lixeira::Lixeira():Obstacle(){
    sp = Sprite("img/lixeira.png", 1, 1);
	this->speed = 0;
	this->layer = rand()%2 + 1;
	this->subLayer = 3;
	this->spriteSound = Sound(-1);
	SetHeight();

    OpenSound("audio/lixeira.wav");
}

Lixeira::~Lixeira(){
    spriteSound.Stop();
}

void Lixeira::Render(){
    this->sp.Render(this->box.x - Camera::GetX(), this->box.y - Camera::GetY() - 10);
}

void Lixeira::NotifyCollision(GameObject* other){
    if(other->Is("Player")){
        spriteSound.Play(1);
    }
}

bool Lixeira::Is(std::string type){
    return type == "Lixeira";
}

int Lixeira::GetLayer(){
    return this->layer;
}

int Lixeira::GetSublayer(){
    return this->subLayer;
}
