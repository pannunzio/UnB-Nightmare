#include "MapActions.h"
#include "Camera.h"

MapActions::MapActions(float x, float y, int layer){
    this->sp = Sprite("img/escada.png");

    this->box.x = x;
    this->box.y = y;
    this->box.w = this->sp.GetWidth();
    this->box.h = this->sp.GetHeight();

    this->subLayer = -1;
    this->layer = layer;
    this->isDead = false;
}

MapActions::~MapActions(){
//    this->sp.~Sprite();
}

void MapActions::Update(float dt){

//    if(box.x - Camera::pos.x +100< 0)
//		this->isDead = true;
}
void MapActions::Render(){
    sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
}

bool MapActions::IsDead(){
    return this->isDead;
}

bool MapActions::Is(std::string type){
    return (type == "Escada");
}

void MapActions::NotifyCollision(GameObject* other){
    if(other->Is("Player")){
        cout << "map action colliding with player" << endl;
    }
}
