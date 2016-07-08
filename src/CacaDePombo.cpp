#include "CacaDePombo.h"
#include "Game.h"
#include "Defines.h"
#include "Camera.h"
#include <math.h>

CacaDePombo::CacaDePombo(float x, float y, string sprite, int frameCount,float frameTime, bool targetsPlayer, float x2, float y2, float s):
        sp(sprite, frameCount, frameTime){

    this->type = type;
	this->targetsPlayer = targetsPlayer;
	Sbox.Centralize(x, y, sp.GetWidth(), sp.GetHeight());
	distanceLeft = 300;
	distanceLimit = 3;
    this->layer = LAYER_TOP;
    this->gravidade = 9.8;
    this->speed.x = 100;
    this->speed.y = 0;
    this->box.x = x2;
    this->box.y = y2;
    this->speedP = s;
}

CacaDePombo::~CacaDePombo(){

}

bool CacaDePombo::IsDead(){
    return this->distanceLeft <= distanceLimit;
}

void CacaDePombo::Update(float dt){
    this->speed.y += gravidade;

        //    this->distanceLeft -= sqrtf((speed.x*speed.x) + (speed.y+speed.y));
    distanceLeft --;
    this->Sbox.x += speed.x * dt;
    this->Sbox.y += speed.y * dt;
    box.x = box.x + speedP*dt*100;
}

void CacaDePombo::Render(){
    sp.Render(Sbox.x - Camera::pos.x, Sbox.y - Camera::pos.y);
}

bool CacaDePombo::Is(std::string type){
    return (type == "Caca");
}

void CacaDePombo::SetSubLayer(int subLayer){
    this->subLayer = subLayer;
}

void CacaDePombo::NotifyCollision(GameObject* other){
    if (other->Is("Player")){
        distanceLimit = 160;
        //toca o som
    }
}

