#include "Pombo.h"
#include "Player.h"
#include "Game.h"
#include "CacaDePombo.h"
#include "Camera.h"

Pombo::Pombo(float x, float y, int subLayer): pombo("img/pombo.png", 4, 0.09), sombra("img/sombraPombo.png"), soundPombo("audio/pombo.wav"){
    cout << "PRU PRU MOTHERFUCKERS" << endl;
    this->layer = LAYER_TOP;
    this->subLayer = subLayer;
    isDead = false;
    this->speed = -3;
	if(speed!=0)
		speed -= rand()%3;
    fazendoCaca = false;
    sBox.Centralize(x, y - 100, pombo.GetWidth(), pombo.GetHeight());

    box.x = sBox.x;			//
    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;
    box.y = box.y - (this->subLayer - 3)*26;

    soundPombo.Play(1);
}

Pombo::~Pombo(){

}

void Pombo::Update(float dt){
    pombo.Update(dt);
    sombra.Update(dt);

	box.x = box.x + speed*dt*100;
    sBox.x = sBox.x + speed*dt*100;
    if(!fazendoCaca && this->sBox.x - Player::player->box.x < 150){
        this->FazCaca();
        fazendoCaca = true;
    }

    if(sBox.x - Camera::pos.x + pombo.GetWidth()< 0)
		this->isDead = true;
}

void Pombo::Render(){
    pombo.RenderFlipped(sBox.x - Camera::pos.x, sBox.y - Camera::pos.y);
    sombra.RenderFlipped(box.x - Camera::pos.x, box.y + 100 - Camera::pos.y);
}

bool Pombo::IsDead(){
    if(isDead){
        soundPombo.Stop(2);
        return true;
    }
    return false;
}

bool Pombo::Is(std::string type){
    return (type == "Pombo");
}

void Pombo::NotifyCollision(GameObject* other){

}

void Pombo::FazCaca(){
    Vec2 shootPos = sBox.CenterPos();
    CacaDePombo* caquinha = new CacaDePombo(shootPos.x, shootPos.y, "img/cacaPombo.png", 3, 1, true, box.x, box.y, speed);
    caquinha->SetSubLayer(subLayer);
    Game::GetInstance().GetCurrentState().AddObject(caquinha);
}

void Pombo::StopSound(){}
