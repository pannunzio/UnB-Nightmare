#include "Acai.h"
#include "Camera.h"
#include "Player.h"

Acai::Acai(int layer, int sublayer){
    this->sp = Sprite("img/ggliko.png", 6, 0.09);

    cout << "SUBLAYER DO ACAI: " << sublayer << endl;

    this->layer = layer;
    this->subLayer = subLayer;

    this->box.x = Player::player->box.x + 1200;
    this->box.y = 0;
    this->box.w = this->sp.GetWidth();
    this->box.h = this->sp.GetHeight();

    this->isDead = false;
//    this->isSoundHappening = false;

    this->captureSound.SetChannel(5);

	if(this->layer == LAYER_TOP)
        this->box.y = ITEM_HEIGHT_L3;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = ITEM_HEIGHT_L2;

    if(this->layer == LAYER_BOTTON)
        this->box.y = ITEM_HEIGHT_L1;

    this->box.y -= (this->subLayer - 3) * 26;

    this->captureSound.Open("audio/comida_getitem.wav", 5);
}

void Acai::Update(float dt){
    if(Player::player){
        this->sp.Update(dt);
    } else
        this->isDead = true;
}

void Acai::Render(){
    this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y);
}


bool Acai::Is(string type){
    return type == "Acai";
}
