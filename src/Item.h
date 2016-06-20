#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"
#include <string>
#include "Camera.h"
#include "Defines.h"

class Item : public GameObject
{
    public:
        Item(int layer, int subLayer, std::string item);
        ~Item();
        bool IsDead();
        void Update(float dt);
        void Render();
        void Use();
        //void SpawnRandom(GameObject* target, ItemType itemType);
        //void SpawnRandom(GameObject* target);
        void NotifyCollision(GameObject* other);
        bool Is(std::string type);
    protected:
    private:
        Vec2 speed;
        Sprite bg;
        string itemType;
        bool isDead;
};

#endif // ITEM_H
