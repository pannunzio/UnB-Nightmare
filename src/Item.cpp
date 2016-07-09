#include "Item.h"
#include "Player.h"

Item::Item(int layer, int subLayer, std::string item)
{
    //ctor
    this->layer = layer;
    this->subLayer = subLayer;
    this->speed = Vec2(CAMERA_NORMAL_SPEED,2);
    this->box = Rect(Player::player->box.x+1200,0,bg.GetWidth(),bg.GetHeight());
    this->itemType = item;
    this->isDead = false;
    this->isSoundHappening = false;
    this->captureSound = Sound();

	//
    if(layer == LAYER_TOP)							//
        box.y=ITEM_HEIGHT_L3;						//
    if(layer == LAYER_MIDDLE)						//
        box.y=ITEM_HEIGHT_L2;						//
    if(layer == LAYER_BOTTON)						//
        box.y=ITEM_HEIGHT_L1;						//
    												//
    box.y = box.y - (this->subLayer - 3)*26;		//
    ///////////////////////////////////////////////////
    if(itemType == "COFFEE"){
        bg= Sprite("img/cafeColor.png", 6, 0.09);
        captureSound.Open("audio/cafe_getitem.wav");
    }
    if(itemType == "SKATE"){
        bg= Sprite("img/skate.png", 6, 0.09);
    }
    if(itemType == "GGLIKO"){
        bg= Sprite("img/ggliko.png", 6, 0.09);
        captureSound.Open("audio/comida_getitem.wav");
    }

    //std::cout << "Item Construido" << std::endl;

}


Item::~Item(){
    cout<<"ITEM DESTRUIDO"<<endl;
}

void Item::Update(float dt){
    if(Player::player){
        bg.Update(dt);
    }
    else
        this->isDead = true;
}

void Item::Render(){
    bg.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
}

void Item::Use(){}

bool Item::IsDead(){
    return this->isDead;
}

void Item::NotifyCollision(GameObject* other){

    if(other->Is("Player")){
        this->isDead = true;
        captureSound.Play(1);
    }
    if(box.x<-100){
        this->isDead = true;
    }
}

bool Item::Is(std::string type){
    return (type == itemType);
}

void Item::StopSound(){
    captureSound.Stop();
}
