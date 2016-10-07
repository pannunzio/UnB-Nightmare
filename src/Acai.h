#ifndef ACAI_H
#define ACAI_H

#include "Item.h"
#include <string>

using std::string;
using std::endl;
using std::cout;

class Acai: public Item{
public:
    Acai(int layer, int sublayer);

    void Update(float dt);
    void Render();

    bool Is(string type);

private:
    Sprite sp;

//    ~Acai();
};

#endif // ACAI_H
