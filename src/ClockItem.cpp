#include <math.h>
#include "ClockItem.h"

ClockItem::ClockItem(int layer, int subLayer){
    this->sp = Sprite("img/clocksprite.png", 5, 0.1);
    SetAssets(layer, subLayer);
    this->timeToAdd = pow(-1, rand()%10) * (rand()%5 + 1);
    SetHeight();
}

bool ClockItem::Is(string type){
    return type == "ClockItem";
}

float ClockItem::GetTimeToAdd(){
    return this->timeToAdd;
}
