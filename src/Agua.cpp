#include "Agua.h"

Agua::Agua(int layer, int subLayer) : sp(AGUA_SPRITE, AGUA_FRAMES, AGUA_FTIME){
	this->isDead = false;
	this->speed = AGUA_SPEED;
	this->layer = layer;
 	this->subLayer = subLayer;

	this->box.x = Player::GetInstance().GetX() + DEFAULT_OBSTACLE_DISTANCE;

	//if(this->layer == LAYER_TOP)
        //this->box.y = OBST_HEIGHT_L3;

    //if(this->layer == LAYER_MIDDLE)
        //this->box.y = OBST_HEIGHT_L2;

    //if(this->layer == LAYER_BOTTON)
        //this->box.y = OBST_HEIGHT_L1;

//    this->box.y += sp.GetHeight();
//	this->box.y -= (this->subLayer - 3) * 26 - 200;

}

Agua::~Agua(){
}

void Agua::Update(float dt){

	this->timer.Update(dt);

	this->sp.Update(dt);
	this->box.x += this->speed * dt * 100;

	if(this->speed == NORMAL_GAME_SPEED){
		this->deadTimer.Update(dt);
		this->box.y += 1 * dt * 100;
		this->deadTimer.Update(dt);
	}
    if(this->box.x - Camera::GetX() <= 0){
    	this->speed = NORMAL_GAME_SPEED;
    }

	if(this->deadTimer.GetCurrentTime() > 5)
		this->isDead = true;
}

void Agua::Render(){
	this->sp.Render(this->box.x, this->box.y - Camera::GetY());
}

bool Agua::IsDead(){
	return this->isDead;
}

void Agua::NotifyCollision(GameObject* other){

}

bool Agua::Is(std::string type){
	return type == AGUA_TYPE;
}

int Agua::GetLayer(){
    return this->layer;
}

int Agua::GetSublayer(){
    return this->subLayer;
}
