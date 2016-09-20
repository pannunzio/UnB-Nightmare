#include "Pombo.h"
#include "Player.h"
#include "Game.h"
#include "CacaDePombo.h"
#include "Camera.h"
#include "Obstacle.h"

Pombo::Pombo(){
    this->sp = Sprite("img/pombo.png", 4, 0.09);
    this->layer = LAYER_TOP;
    this->subLayer = 0;
    this->isDead = false;
    this->speed = -3;

    this->fazendoCaca = false;
    this->box.Centralize(Player::player->box.x + 1000, ITEM_HEIGHT_L3 - 150, this->sp.GetWidth(), this->sp.GetHeight());

    OpenSound("audio/pombo.wav");
    this->spriteSound.Play(1);
}

Pombo::~Pombo(){
    this->spriteSound.Stop();
}

void Pombo::Update(float dt){
    this->sp.Update(dt);

	this->box.x += this->speed * dt * 100;

    if(!this->fazendoCaca && this->box.x - Player::player->box.x < 120){
        cout << "FAENDO CAQUINHA!!" << endl;
        this->FazCaca();
        this->fazendoCaca = true;
    }

    if(this->box.x - Camera::pos.x + this->sp.GetWidth() < 0)
		this->isDead = true;
}

void Pombo::Render(){
    this->sp.RenderFlipped(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y);
}

void Pombo::NotifyCollision(GameObject* other){
    //pombo não collide com nada
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
    Vec2 shootPos = box.CenterPos();
    CacaDePombo* caquinha = new CacaDePombo(shootPos.x, shootPos.y, "img/cacaPombo.png", 3, 1, true, box.x, box.y, speed);
    caquinha->SetSubLayer(Player::player->GetSublayer());
    Game::GetInstance().GetCurrentState().AddObject(caquinha);
}
