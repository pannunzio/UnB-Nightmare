#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "GameObject.h"
#include "Camera.h"
#include "Defines.h"

class Item : public GameObject{
public:
//    Item(int layer, int subLayer, std::string item);
    ~Item();

    bool IsDead();
    void NotifyCollision(GameObject* other);
//    bool Is(std::string type);

    int GetLayer();
	int GetSublayer();

    bool isDead;
    Sound captureSound;
//    bool isSoundHappening;
};

#endif


//#ifndef ITEM_H
//#define ITEM_H
//
//#include <string>
//
//#include "GameObject.h"
//#include "Camera.h"
//#include "Defines.h"
//
//class Item : public GameObject{
//public:
//    Item(int layer, int subLayer, std::string item);
//    ~Item();
//
//    void Update(float dt);
//    void Render();
//    bool IsDead();
//    void NotifyCollision(GameObject* other);
//    bool Is(std::string type);
//
//    int GetLayer();
//	int GetSublayer();
//
//protected:
//
//private:
//    Sprite bg;
//    string itemType;
//    bool isDead;
//
//    Sound captureSound;
//    bool isSoundHappening;
//};
//
//#endif
