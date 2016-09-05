#include "Item.h"
#include "Player.h"

Item::Item(int layer, int subLayer, std::string item) {
    //ctor
    this->layer = layer;
    this->subLayer = subLayer;
    this->speed = Vec2(CAMERA_NORMAL_SPEED, 2);
    this->box = Rect(Player::player->box.x + 1200, 0, bg.GetWidth(), bg.GetHeight());
    this->itemType = item;
    this->isDead = false;
    this->isSoundHappening = false;
    this->captureSound = Sound();

	if(this->layer == LAYER_TOP)
        this->box.y = ITEM_HEIGHT_L3;
    if(this->layer == LAYER_MIDDLE)
        this->box.y = ITEM_HEIGHT_L2;
    if(this->layer == LAYER_BOTTON)
        this->box.y = ITEM_HEIGHT_L1;

    this->box.y -= (this->subLayer - 3) * 26;

    if(this->itemType == "COFFEE"){
        this->bg = Sprite("img/cafeColor.png", 6, 0.09);
        this->captureSound.Open("audio/cafe_getitem.wav");
    }

    if(this->itemType == "SKATE"){
        this->bg = Sprite("img/skate.png", 6, 0.09);
    }

    if(this->itemType == "GGLIKO"){
        this->bg = Sprite("img/ggliko.png", 6, 0.09);
        this->captureSound.Open("audio/comida_getitem.wav");
    }
}

Item::~Item(){
    cout<<"ITEM DESTRUIDO"<<endl;
}

void Item::Update(float dt){
    if(Player::player){
        this->bg.Update(dt);
    } else
        this->isDead = true;
}

void Item::Render(){
    this->bg.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y);
}

bool Item::IsDead(){
    return this->isDead;
}

void Item::NotifyCollision(GameObject* other){
    if(other->Is("Player")){
        this->isDead = true;
        this->captureSound.Play(1);
    }

    if(this->box.x < -100){
        this->isDead = true;
    }
}

bool Item::Is(std::string type){
    return (type == itemType);
}

void Item::Use(){
}

void Item::StopSound(){
    this->captureSound.Stop();
}
