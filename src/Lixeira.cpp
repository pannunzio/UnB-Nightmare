#include "Lixeira.h"

Lixeira::Lixeira(int layer){
    sp = Sprite("img/lixeira.png", 1, 1);
	this->speed = 0;
	this->canBlock = true;
	this->isDead = false;

	this->layer = layer;
	this->subLayer = 3;

	this->spriteSound = Sound(-1);

    this->box.x = Player::GetInstance().GetX() + 1200;

    if(this->layer == LAYER_TOP)
        this->box.y = LAYER_TOP_HEIGHT;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = LAYER_MIDDLE_HEIGHT;

    if(this->layer == LAYER_BOTTON)
        this->box.y = LAYER_BOTTON_HEIGHT;

    this->box.y += 20;
    this->box.y -= (this->subLayer - 3) * 26;

    OpenSound("audio/lixeira.wav");
}

Lixeira::~Lixeira(){
    spriteSound.Stop();
}

void Lixeira::Render(){
    this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 10);
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
