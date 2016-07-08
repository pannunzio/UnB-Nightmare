/*
 * Animation.cpp
 *
 *  Created on: 5 de mai de 2016
 *      Author: Caio
 */

#include "Animation.h"
#include "Camera.h"

void Animation::NotifyCollision(GameObject* other){

}
bool Animation::Is(std::string type){
	return (type == "Animation");
}

Animation::Animation(float x, float y, float rotation, std::string spr, int frameCount, float frameTime, bool ends){
	sp = Sprite(spr,frameCount,frameTime);
	box.Centralize(x,y,this->sp.GetWidth(),this->sp.GetHeight());

	this->rotation = rotation;
	oneTimeOnly = ends;
	timeLimit = frameTime*frameCount;
	subLayer = 1;
	layer = 1;
}

void Animation::Update(float dt){
	sp.Update(dt);
	endTimer.Update(dt);

}
void Animation::Render(){
	sp.Render(box.x - Camera::pos.x,box.y - Camera::pos.y);

}
bool Animation::IsDead(){
	if(endTimer.Get()>=timeLimit)
		return true;
	return false;

}

