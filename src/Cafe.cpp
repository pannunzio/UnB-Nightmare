#include "Cafe.h"
#include "Camera.h"
#include "Player.h"

Cafe::Cafe(int layer, int subLayer){
    this->sp = Sprite("img/cafeColor.png", 6, 0.09);

    this->layer = layer;
    this->subLayer = subLayer;

    this->box.x = Player::player->box.x + 1200;
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

    this->captureSound.Open("audio/cafe_getitem.wav", 5);
}

bool Cafe::Is(string type){
    return type == "Cafe";
}
