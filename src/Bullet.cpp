#include "Bullet.h"

Bullet::Bullet(float originX, float originY) :  sp(BULLET_SPRITE, BULLET_FRAMECOUNT, BULLET_FRAMETIME),
                                                shooterSound("audio/cafe_shoot.wav", 6)
{
    this->sp.SetAnimationTimes(1);
    this->layer = Player::GetInstance().GetLayer();
    this->subLayer = Player::GetInstance().GetSublayer();
	this->speed = 10;

	this->box.Centralize(originX, originY, this->sp.GetWidth(), this->sp.GetHeight());

	distanceLeft = BULLET_MAX_DISTANCE;
	shooterSound.Play(1);
}

Bullet::~Bullet() {

}

void Bullet::Update(float dt){
	sp.Update(dt);
	box.x += speed * dt * 100;
	distanceLeft -= speed * dt * 100;

}
void Bullet::Render(){
	sp.Render(box.x - Camera::GetX(), box.y - Camera::GetY(), box.rotation);
}

bool Bullet::IsDead(){
	if(distanceLeft <= 0 )
		return true;
	return false;
}

void Bullet::NotifyCollision(GameObject* other){
	if(other->Is("Zumbi") || other->Is("Pessoa")){
		distanceLeft = 0;
	}
}

bool Bullet::Is(std::string type){
	return(type == "Coffee");
}


int Bullet::GetLayer(){
    return this->layer;
}

int Bullet::GetSublayer(){
    return this->subLayer;
}
