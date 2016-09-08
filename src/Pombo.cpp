#include "Pombo.h"
#include "Player.h"
#include "Game.h"
#include "CacaDePombo.h"
#include "Camera.h"

Pombo::Pombo(float x, float y, int subLayer): pombo("img/pombo.png", 4, 0.09), sombra("img/sombraPombo.png"), soundPombo("audio/pombo.wav"){
    this->layer = LAYER_TOP;
    this->subLayer = subLayer;
    this->isDead = false;
    this->speed = -3;

	if(this->speed != 0)
		this->speed -= rand()%3;

    this->fazendoCaca = false;
    this->sBox.Centralize(x, y - 100, this->pombo.GetWidth(), this->pombo.GetHeight());

    this->box.x = this->sBox.x;

    if(this->layer == LAYER_TOP)
        this->box.y = ITEM_HEIGHT_L3;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = ITEM_HEIGHT_L2;

    if(this->layer == LAYER_BOTTON)
        this->box.y = ITEM_HEIGHT_L1;

    this->box.y -= (this->subLayer - 3) * 26;
    this->soundPombo.Play(1);
}

Pombo::~Pombo(){

}

void Pombo::Update(float dt){
    this->pombo.Update(dt);
    this->sombra.Update(dt);

	this->box.x += this->speed * dt * 100;
    this->sBox.x += this->speed * dt * 100;

    if(!this->fazendoCaca && this->sBox.x - Player::player->box.x < 150){
        this->FazCaca();
        this->fazendoCaca = true;
    }

    if(this->sBox.x - Camera::pos.x + this->pombo.GetWidth()< 0)
		this->isDead = true;
}

void Pombo::Render(){
    this->pombo.RenderFlipped(this->sBox.x - Camera::pos.x, this->sBox.y - Camera::pos.y);
    this->sombra.RenderFlipped(this->box.x - Camera::pos.x, this->box.y + 100 - Camera::pos.y);
}

bool Pombo::IsDead(){
    if(this->isDead){
        this->soundPombo.Stop(2);

        return true;
    }
    return false;
}

void Pombo::NotifyCollision(GameObject* other){

}

bool Pombo::Is(std::string type){
    return (type == "Pombo");
}


int Pombo::GetLayer(){
    return this->layer;
}

int Pombo::GetSublayer(){
    return this->subLayer;
}


void Pombo::FazCaca(){
    Vec2 shootPos = sBox.CenterPos();
    CacaDePombo* caquinha = new CacaDePombo(shootPos.x, shootPos.y, "img/cacaPombo.png", 3, 1, true, box.x, box.y, speed);
    caquinha->SetSubLayer(subLayer);
    Game::GetInstance().GetCurrentState().AddObject(caquinha);
}
