#include "Skate.h"
#include "Camera.h"
#include "Player.h"

Skate::Skate(int layer, int subLayer){
    this->sp = Sprite("img/skate.png", 6, 0.09);
    SetAssets(layer, subLayer);
}

bool Skate::Is(string type){
    return type == "Skate";
}
