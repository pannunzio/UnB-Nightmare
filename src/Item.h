#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "GameObject.h"
#include "Camera.h"
#include "Defines.h"

class Item : public GameObject{
public:
    Item(int layer, int subLayer, std::string item);
    ~Item();

    void Update(float dt);
    void Render();
    bool IsDead();
    void NotifyCollision(GameObject* other);
    bool Is(std::string type);

    void Use();
    //void SpawnRandom(GameObject* target, ItemType itemType);
    //void SpawnRandom(GameObject* target);
    void StopSound();

protected:

private:
    Vec2 speed;
    Sprite bg;
    string itemType;
    bool isDead;

    Sound captureSound;
    bool isSoundHappening;
};

#endif
