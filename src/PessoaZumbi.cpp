#include "PessoaZumbi.h"
#include "Camera.h"
#include "Player.h"
#include "Defines.h"

PessoaZumbi::PessoaZumbi(){
    GetSprite();
	this->speed = 2.5 + rand()%10/10;
	this->canBlock = true;
	this->isDead = false;
	this->layer = rand()%3 + 1;
	this->subLayer = rand()%3 + 1;

	this->spriteSound = Sound(-1);

    GetZombieSound();
    this->spriteSound.Play(1);

	this->box.x = Player::player->box.x + 1200;

   if(this->layer == LAYER_TOP)
        this->box.y = ITEM_HEIGHT_L3 + 3;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = ITEM_HEIGHT_L2 + 10;

    if(this->layer == LAYER_BOTTON)
        this->box.y = ITEM_HEIGHT_L1 + 7;

    this->box.y -= (this->subLayer - 3) * 25;
}

PessoaZumbi::~PessoaZumbi(){
    spriteSound.Stop();
}

void PessoaZumbi::Render(){
    if(this->speed >= 0)
        this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 30);
    else
        this->sp.RenderFlipped(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 30);
}

void PessoaZumbi::NotifyCollision(GameObject* other){
    if(other->Is("Coffee")){
        ChangeSprite();
    }
}

bool PessoaZumbi::Is(string type){
    return type == "Zumbi";
}

int PessoaZumbi::GetLayer(){
    return this->layer;
}

int PessoaZumbi::GetSublayer(){
    return this->subLayer;
}

void PessoaZumbi::GetSprite(){
    this->sp = Sprite("img/meninazumbi.png", 6, 0.2);
}

void PessoaZumbi::GetZombieSound(){
    string fileName;

    switch (rand()%6){
    case 0:{
        fileName = "audio/Zumbi0.ogg";
    }
    case 1:{
        fileName = "audio/Zumbi2.ogg";
    }
    case 2:{
        fileName = "audio/Zumbi3.ogg";
    }
    case 3:{
        fileName = "audio/Zumbi6.ogg";
    }
    case 4:{
        fileName = "audio/Zumbi7.ogg";
    }
    case 5:{
        fileName = "audio/Zumbi8.ogg";
    }
    case 6:{
        fileName = "audio/Zumbi9.ogg";
    }
    }
    OpenSound(fileName);
}

void PessoaZumbi::ChangeSprite(){
    this->sp = Sprite("img/menina.png", 6, 0.2);
    this->sp.SetClip(this->box.x, this->box.y, this->sp.GetWidth(), this->sp.GetHeight());
    this->speed = 8;
}
