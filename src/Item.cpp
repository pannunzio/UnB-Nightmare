#include "Item.h"
#include "Player.h"

Item::Item(int layer, int subLayer, std::string item)
{
    //ctor
    this->layer = layer;
    this->subLayer = subLayer;
    this->speed = CAMERA_NORMAL_SPEED;
    beingUsed = 0;
    //box.Centralize(Player::player->box.x - Camera::pos.x+1200,Player::player->box.y - Camera::pos.y+80,bg.GetWidth(),bg.GetHeight());

    if(subLayer==SUBLAYER_BOTTON){
        box.Centralize(1355,370,bg.GetWidth(),bg.GetHeight());
        std::cout << "BOTTON";
    }
    if(subLayer==SUBLAYER_TOP){
        box.Centralize(1355,330,bg.GetWidth(),bg.GetHeight());
        std::cout << "  TOP";
    }
    if(subLayer==SUBLAYER_MIDDLE){
        box.Centralize(1355,350,bg.GetWidth(),bg.GetHeight());
        std::cout << "MIDDLE";
    }
    if(item == "COFFEE"){
        itemType = COFFEE;
        bg= Sprite("img/coffee.png",3,0.1);
    }
    if(item == "SKATE"){
        itemType = SKATE;
        bg= Sprite("img/coffee.png");
    }
    if(item == "OUTRO"){
        itemType = OUTRO;
        bg= Sprite("img/coffee.png");
    }

    //std::cout << "Item Construido" << std::endl;

}

void Item::Update(float dt){
    int X, W;
    bg.Update(dt);
	box.x = box.x - speed*dt*100;
	X = Player::player->box.x - Camera::pos.x;
	W = Player::player->box.w / 2;
    if(Player::player->layer == layer && Player::player->subLayer==subLayer){
        if((box.x<(X+W))&&(box.x>(X-W)))
            beingUsed = 2;
    }
	//std::cout << "ITEM: " <<box.x << "|||"<<box.y << std::endl;
}

void Item::Render(){
    bg.Render(box.x , box.y);
}

void Item::Use(){}

bool Item::IsDead(){
    if(beingUsed==2||box.x<-100)
        return true;
    return false;
}

void Item::NotifyCollision(GameObject* other){
//    if(other->Is("Player")){
//        if(other->subLayer==subLayer){
//            beingUsed = 2;
//            std::cout << "ITEM: " <<other->subLayer<< "|||"<<subLayer << std::endl;
//        }
//        std::cout << "ITEM: " <<other->subLayer<< "|||"<<subLayer << std::endl;
//    }

}

//void Item::SpawnRandom(GameObject* target){}

bool Item::Is(std::string type){
    if(type == "Item")
        return true;
    return false;
}
