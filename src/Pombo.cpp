#include "Pombo.h"
#include "Camera.h"

Pombo::Pombo(){

}

Pombo::~Pombo(){

}

void Pombo::Update(float dt){

}

void Pombo::Render(){
    this->pombo.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y, this->rotation);
    this->sombra.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y, this->rotation);
}

bool Pombo::IsDead(){
    return false;
}

bool Pombo::Is(std::string type){
    return type=="Pombo";
}

void Pombo::NotifyCollision(GameObject* other){

}
