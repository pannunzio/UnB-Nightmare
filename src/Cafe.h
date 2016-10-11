#ifndef CAFE_H
#define CAFE_H

#include <string>

#include "Item.h"
#include "Camera.h"
#include "Player.h"

using std::string;
using std::cout;
using std::endl;

class Cafe: public Item{
public:
    Cafe(int layer, int subLayer);

    bool Is(string type);

//    void SetAssets();
};

#endif
