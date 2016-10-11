#include "Cafe.h"

Cafe::Cafe(int layer, int subLayer){
    this->sp = Sprite("img/cafeColor.png", 6, 0.09);
    this->captureSound.Open("audio/cafe_getitem.wav", 5);
    SetAssets(layer, subLayer);
}

bool Cafe::Is(string type){
    return type == "Cafe";
}
//
//void Cafe::SetAssets(){
//
//}
