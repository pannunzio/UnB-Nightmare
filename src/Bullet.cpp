#include "Bullet.h"

Bullet::Bullet(float x, float y,  float speed, string sprite, int frameCount,float frameTime, bool targetsPlayer, std::string type)
		: sp(sprite,frameCount,frameTime), shooterSound("audio/cafe_shoot.wav", 6)
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
        box.y=LAYER_TOP_HEIGHT;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=LAYER_MIDDLE;						//
    if(layer == LAYER_BOTTON)						//
        box.y=LAYER_BOTTON_HEIGHT;						//
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
	if(other->Is("Zumbi") || other->Is("Pessoa")){
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
