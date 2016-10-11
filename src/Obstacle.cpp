#include "Obstacle.h"

void Obstacle::Update(float dt){
	this->sp.Update(dt);
	this->box.x += this->speed * dt * 100;

    if(this->box.x - Camera::pos.x + this->sp.GetWidth()< 0){
		this->isDead = true;
        this->spriteSound.Stop();
    }
}

bool Obstacle::IsDead(){
    return this->isDead;
}

void Obstacle::OpenSound(string fileName){
    this->spriteSound.Open(fileName, 4);
}

void Obstacle::ChangeSpritesheet(string fileName, int frameCount, float frameTime){
    this->sp.Open(fileName);
    this->sp.SetFrameCount(frameCount);
    this->sp.SetFrameTime(frameTime);
    this->sp.SetClip(this->box.x, this->box.y, this->sp.GetWidth(), this->sp.GetHeight());
}
