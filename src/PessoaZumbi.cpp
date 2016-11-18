#include "PessoaZumbi.h"

PessoaZumbi::PessoaZumbi():Obstacle(){
    GetSprite();
	this->spriteSound = Sound(3);
    GetZombieSound();
    this->spriteSound.Play(1);
    SetHeight();
}

PessoaZumbi::~PessoaZumbi(){
    spriteSound.Stop();
}

void PessoaZumbi::Render(){
    if(this->speed >= 0)
        this->sp.Render(this->box.x - Camera::GetX(), this->box.y - Camera::GetY());
    else
        this->sp.RenderFlipped(this->box.x - Camera::GetX(), this->box.y - Camera::GetY());
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

    this->spriteSound.Open(fileName, 3);
}

void PessoaZumbi::ChangeSprite(){
    this->sp = Sprite("img/menina.png", 6, 0.2);
    this->sp.SetClip(this->box.x, this->box.y, this->sp.GetWidth(), this->sp.GetHeight());
    this->speed = 8;
}
