#ifndef SKATE_H
#define SKATE_H

#include "Item.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

class Skate: public Item{
public:
    Skate(int layer, int subLayer);

    bool Is(string type);

//    void SetAssets();
};

#endif

