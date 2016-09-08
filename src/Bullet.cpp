#include "Bullet.h"
#include "Camera.h"
#include "Game.h"
#include "Defines.h"
#include "Player.h"

Bullet::Bullet(float x, float y,  float speed, string sprite, int frameCount,float frameTime, bool targetsPlayer, std::string type)
		: sp(sprite,frameCount,frameTime), shooterSound("audio/cafe_shoot.wav")
{
    this->layer = 2;
    this->subLayer = 2;
	this->type = type;
	this->speed = speed;
	this->targetsPlayer = targetsPlayer;
	box.Centralize(x,y,sp.GetWidth(),sp.GetHeight());
	distanceLeft = BULLET_MAX_DISTANCE;
	shooterSound.Play(1);
//	shooterSound.SetVolume(100);
}

Bullet::~Bullet() {

}

void Bullet::Update(float dt){
	sp.Update(dt);
	box.x = box.x + speed*dt*100;
	distanceLeft-= speed*dt*100;

    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;						//
    												//
    box.y = box.y - (this->subLayer - 3)*26;		//
    ///////////////////////////////////////////////////


}
void Bullet::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y + 30,rotation);
}

bool Bullet::IsDead(){
	if(distanceLeft <= 0 )
		return true;
	return false;
}

void Bullet::NotifyCollision(GameObject* other){
	if(other->Is("menina")){
		distanceLeft = 0;
		std::cout << "colidiu com a menina" << std::endl;
	}


}

bool Bullet::Is(std::string type){
	return(type == this->type);
}


int Bullet::GetLayer(){
    return this->layer;
}

int Bullet::GetSublayer(){
    return this->subLayer;
}


void Bullet::SetLayers(int layer, int subLayer){
    this->layer = layer;
    this->subLayer = subLayer;
}
