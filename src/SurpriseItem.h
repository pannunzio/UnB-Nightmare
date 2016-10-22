#ifndef SURPRISEITEM_H
#define SURPRISEITEM_H

#include "Item.h"
#include "Camera.h"
#include "Player.h"

using std::string;
using std::endl;
using std::cout;

class SurpriseItem: public Item{
public:
    SurpriseItem(int layer, int subLayer);

    bool Is(string type);
    int GetSublayer();

    SurpriseType GetSurprise();

private:
    SurpriseType surprise;
};

#endif // SURPRISEITEM_H
