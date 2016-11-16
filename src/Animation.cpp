#include "Animation.h"

Animation::Animation(float x, float y, float rotation, std::string spr, int frameCount, float frameTime, bool ends){
	this->sp = Sprite(spr,frameCount,frameTime);

	this->box.Centralize(x, y, this->sp.GetWidth(), this->sp.GetHeight());

	this->box.rotation = rotation;

	this->oneTimeOnly = ends;
	this->timeLimit = frameTime * frameCount;
	this->subLayer = 1;
	this->layer = 1;
}

void Animation::Update(float dt){
	this->sp.Update(dt);
	this->endTimer.Update(dt);
}

void Animation::Render(){
	this->sp.Render(this->box.x - Camera::GetX(), this->box.y - Camera::GetX());
}

bool Animation::IsDead(){
	return this->endTimer.GetCurrentTime() >= this->timeLimit;
}

void Animation::NotifyCollision(GameObject* other){
}

bool Animation::Is(std::string type){
	return (type == "Animation");
}

int Animation::GetLayer(){
    return this->layer;
}

int Animation::GetSublayer(){
    return this->subLayer;
}
