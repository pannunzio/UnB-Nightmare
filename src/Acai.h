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

    bool Is(string type);

private:

};

#endif // ACAI_H
