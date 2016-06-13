#include "Item.h"
#include "Player.h"

Item::Item(int layer, int subLayer, std::string item)
{
    //ctor
    this->layer = layer;
    this->subLayer = subLayer;
    this->speed = Vec2(CAMERA_NORMAL_SPEED,2);
    beingUsed = 0;
    this->box = Rect(Player::player->box.x+1200,0,bg.GetWidth(),bg.GetHeight());

//    if(subLayer==SUBLAYER_BOTTON){
//        box.Centralize(1355,305,bg.GetWidth(),bg.GetHeight());
//        std::cout << "BOTTON";
//    }
//    if(subLayer==SUBLAYER_TOP){
//        box.Centralize(1355,265,bg.GetWidth(),bg.GetHeight());
//        std::cout << "  TOP";
//    }
//    if(subLayer==SUBLAYER_MIDDLE){
//        box.Centralize(1355,285,bg.GetWidth(),bg.GetHeight());
//        std::cout << "MIDDLE";
//    }

    if(layer == LAYER_TOP){
        box.y=ITEM_HEIGHT_L3;
    }
    if(layer == LAYER_MIDDLE){
        box.y=ITEM_HEIGHT_L2;
    }
    if(layer == LAYER_BOTTON){
        box.y=ITEM_HEIGHT_L1;
    }
    box.y = box.y - (this->subLayer - 3)*20;

    if(item == "COFFEE"){
        itemType = COFFEE;
        bg= Sprite("img/cafe.png");
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
	X = Player::player->box.x;
	W = Player::player->box.w / 2;
    if(Player::player->layer == layer && Player::player->subLayer==subLayer){
        if((box.x<(X+W))&&(box.x>(X-W))){
            beingUsed = 2;
            //caso do cafe, joao arruma isso dps
            Player::coffee_ammo++;
        }
    }

}

void Item::Render(){
    bg.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
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
