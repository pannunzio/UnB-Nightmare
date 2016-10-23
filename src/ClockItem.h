#ifndef CLOCKITEM_H
#define CLOCKITEM_H

#include "Item.h"
#include "Camera.h"
#include "Player.h"

using std::string;
using std::cout;
using std::endl;

class ClockItem : public Item{
public:
    ClockItem(int layer, int subLayer);

    bool Is(string type);
    float GetTimeToAdd();

private:
    float timeToAdd;
};

#endif // CLOCKITEM_H
