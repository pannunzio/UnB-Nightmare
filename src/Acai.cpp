#include "Acai.h"

Acai::Acai(int layer, int subLayer){
    this->sp = Sprite("img/acai.png", 6, 0.09);
    this->captureSound.Open("audio/comida_getitem.wav", 5);
    SetAssets(layer, subLayer);
}

bool Acai::Is(string type){
    return type == "Acai";
}
