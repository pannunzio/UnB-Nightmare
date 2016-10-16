#include "Item.h"

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

void Item::SetAssets(int layer, int subLayer){
    this->layer = layer;
    this->subLayer = subLayer;

    this->box.x = Player::GetInstance().GetX() + 1200;
    this->box.y = 0;
    this->box.w = this->sp.GetWidth();
    this->box.h = this->sp.GetHeight();

    this->isDead = false;

    this->captureSound.SetChannel(5);

	if(this->layer == LAYER_TOP)
        this->box.y = ITEM_HEIGHT_L3;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = ITEM_HEIGHT_L2;

    if(this->layer == LAYER_BOTTON)
        this->box.y = ITEM_HEIGHT_L1;

    if (this->subLayer < SUBLAYER_TOP)
        this->box.y += SUBLAYER_DISTANCE;

    if(this->subLayer == SUBLAYER_BOTTON)
        this->box.y += SUBLAYER_DISTANCE;
}
