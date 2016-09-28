#include "Timer.h"

Timer::Timer(){
	this->currentTime = 0;
}
void Timer::Update(float dt){
	this->currentTime += dt;
}
void Timer::Restart(){
	this->currentTime = 0;
}
float Timer::GetCurrentTime(){
	return this->currentTime;
}
void Timer::SetTimer(float time){
    this->timer = time;
}
bool Timer::isFinished(){
    if(this->currentTime > this->timer) return true;
    else return false;
}
