#include "Item.h"
#include "Player.h"

//Item::Item(int layer, int subLayer, std::string item) {
//    //ctor
//    this->layer = layer;
//    this->subLayer = subLayer;
//    this->box = Rect(Player::player->box.x + 1200, 0, sp.GetWidth(), sp.GetHeight());
//    this->itemType = item;
//    this->isDead = false;
////    this->isSoundHappening = false;
//
//    this->captureSound.SetChannel(5);
//
//	if(this->layer == LAYER_TOP)
//        this->box.y = ITEM_HEIGHT_L3;
//    if(this->layer == LAYER_MIDDLE)
//        this->box.y = ITEM_HEIGHT_L2;
//    if(this->layer == LAYER_BOTTON)
//        this->box.y = ITEM_HEIGHT_L1;
//
//    this->box.y -= (this->subLayer - 3) * 26;
//
//    if(this->itemType == "COFFEE"){
//        this->sp = Sprite("img/cafeColor.png", 6, 0.09);
//        this->captureSound.Open("audio/cafe_getitem.wav", 5);
//    }
//
//    if(this->itemType == "SKATE"){
//        this->sp = Sprite("img/skate.png", 6, 0.09);
//    }
//
//    if(this->itemType == "GGLIKO"){
//        this->sp = Sprite("img/ggliko.png", 6, 0.09);
//        this->captureSound.Open("audio/comida_getitem.wav", 5);
//    }
//}

Item::~Item(){
    this->captureSound.Stop();
}

void Item::Update(float dt){
    if(Player::player){
        this->sp.Update(dt);
    } else
        this->isDead = true;
}

void Item::Render(){
    this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y);
}


bool Item::IsDead(){
    return this->isDead;
}

void Item::NotifyCollision(GameObject* other){
    if(other->Is("Player")){
        cout << "BATI NO PLAYERRR SL: " << this->GetSublayer() << " SUB:: " << this->subLayer << endl;
        this->isDead = true;
        this->captureSound.Play(1);
    }

    if(this->box.x < -100){
        this->isDead = true;
    }
}

int Item::GetLayer(){
    return this->layer;
}

int Item::GetSublayer(){
    return this->subLayer;
}
