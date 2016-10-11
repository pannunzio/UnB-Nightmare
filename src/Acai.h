#ifndef ACAI_H
#define ACAI_H

#include <string>

#include "Item.h"
#include "Camera.h"
#include "Player.h"

using std::string;
using std::endl;
using std::cout;

class Acai: public Item{
public:
    Acai(int layer, int sublayer);

    bool Is(string type);

//    void SetAssets();

private:

};

#endif // ACAI_H
