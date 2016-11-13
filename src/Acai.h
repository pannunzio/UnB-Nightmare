#ifndef ACAI_H
#define ACAI_H

#include <string>

#include "Item.h"
#include "Player.h"

/******
    Acai Defines
******/
#define ACAI_TYPE "Acai"

#define ACAI_SPRITE "img/acai.png"
#define ACAI_FRAMES 6
#define ACAI_FTIME  0.09

#define ACAI_AUDIO  "audio/comida_getitem.wav"

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
