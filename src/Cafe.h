#ifndef CAFE_H
#define CAFE_H

#include "Item.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

class Cafe: public Item{
public:
    Cafe(int layer, int subLayer);

    bool Is(string type);
};

#endif
