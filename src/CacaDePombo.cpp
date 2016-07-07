#include "CacaDePombo.h"
#include "Game.h"
#include "Defines.h"
#include "Camera.h"
#include <math.h>

CacaDePombo::CacaDePombo(float x, float y, string sprite, int frameCount,float frameTime, bool targetsPlayer):
        sp(sprite, frameCount, frameTime){

    this->type = type;
	this->targetsPlayer = targetsPlayer;
	box.Centralize(x, y, sp.GetWidth(), sp.GetHeight());
	distanceLeft = 150;

    this->gravidade = 9.8;
    this->speed.x = 100;
    this->speed.y = 0;
}

CacaDePombo::~CacaDePombo(){

}

bool CacaDePombo::IsDead(){
    return this->distanceLeft <= 3;
}

void CacaDePombo::Update(float dt){
    this->speed.y += gravidade;

        //    this->distanceLeft -= sqrtf((speed.x*speed.x) + (speed.y+speed.y));
    distanceLeft --;
    this->box.x += speed.x * dt;
    this->box.y += speed.y * dt;
}

void CacaDePombo::Render(){
    sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
}

bool CacaDePombo::Is(std::string type){
    return type == "Caca";
}

void CacaDePombo::SetSubLayer(int subLayer){
    this->subLayer = subLayer;
}

void CacaDePombo::NotifyCollision(GameObject* other){
    if (other->Is("Player")){
        distanceLeft = 0;
        //toca o som
    }
}

