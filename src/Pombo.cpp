#include "Pombo.h"
#include "Player.h"
#include "Game.h"
#include "CacaDePombo.h"
#include "Camera.h"

Pombo::Pombo(float x, float y, int subLayer): pombo("img/pombo.png", 4, 0.09), sombra("img/sombraPombo.png"){
    cout << "PRU PRU MOTHERFUCKERS" << endl;
    this->layer = LAYER_TOP;
    this->subLayer = subLayer;
    isDead = false;
    this->speed = -3;
	if(speed!=0)
		speed -= rand()%3;

    fazendoCaca = false;
    box.Centralize(x, y - 100, pombo.GetWidth(), pombo.GetHeight());

}

Pombo::~Pombo(){

}

void Pombo::Update(float dt){
    pombo.Update(dt);
    sombra.Update(dt);

	box.x = box.x + speed*dt*100;

    if(!fazendoCaca && this->box.x - Player::player->box.x < 150){
        this->FazCaca();
        fazendoCaca = true;
    }

    if(box.x - Camera::pos.x + pombo.GetWidth()< 0)
		this->isDead = true;
}

void Pombo::Render(){
    pombo.RenderFlipped(box.x - Camera::pos.x, box.y - Camera::pos.y);
    sombra.RenderFlipped(box.x - Camera::pos.y, box.y + 100 - Camera::pos.y);
}

bool Pombo::IsDead(){
    return isDead;
}

bool Pombo::Is(std::string type){
    return type == "Pombo";
}

void Pombo::NotifyCollision(GameObject* other){

}

void Pombo::FazCaca(){
    Vec2 shootPos = box.CenterPos();
    CacaDePombo* caquinha = new CacaDePombo(shootPos.x, shootPos.y, "img/cacaPombo.png", 1, 1, true);
    caquinha->SetSubLayer(subLayer);
    Game::GetInstance().GetCurrentState().AddObject(caquinha);
}
