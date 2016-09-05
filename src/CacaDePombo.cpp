#include "CacaDePombo.h"
#include "Game.h"
#include "Defines.h"
#include "Camera.h"
#include <math.h>

CacaDePombo::CacaDePombo(float x, float y, string sprite, int frameCount,float frameTime, bool targetsPlayer, float x2, float y2, float s):
        sp(sprite, frameCount, frameTime), colisaoPlayer("audio/caca_explosao.wav"){

    this->type = type;
	this->targetsPlayer = targetsPlayer;
	this->Sbox.Centralize(x, y, this->sp.GetWidth(), this->sp.GetHeight());
	this->distanceLeft = 300;
	this->distanceLimit = 3;
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

void CacaDePombo::Update(float dt){
    this->speed.y += this->gravidade;

        //    this->distanceLeft -= sqrtf((speed.x*speed.x) + (speed.y+speed.y));
    this->distanceLeft --;
    this->Sbox.x += this->speed.x * dt;
    this->Sbox.y += this->speed.y * dt;
    this->box.x += this->speedP * dt * 100;
}

void CacaDePombo::Render(){
    this->sp.Render(this->Sbox.x - Camera::pos.x, this->Sbox.y - Camera::pos.y);
}

bool CacaDePombo::IsDead(){
    if (this->distanceLeft <= distanceLimit){
        if(this->colisaoPlayer.IsPlaying())
            this->colisaoPlayer.Stop(2);
        return true;
    }
    return false;
}

void CacaDePombo::NotifyCollision(GameObject* other){
    if (other->Is("Player")){
        this->distanceLimit = 160;
        this->colisaoPlayer.PlayArbitraryFadeIn(1, 2);
    }
}
bool CacaDePombo::Is(std::string type){
    return (type == "Caca");
}

void CacaDePombo::SetSubLayer(int subLayer){
    this->subLayer = subLayer;
}

void CacaDePombo::StopSound(){
}
