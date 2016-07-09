#ifndef MAPACTIONS_H
#define MAPACTIONS_H

#include "GameObject.h"
#include "Sprite.h"
#include <string>

class MapActions: public GameObject{
public:
    MapActions(float x, float y, int layer);
    ~MapActions();

    void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);
	void StopSound();

    Rect box;
private:
    Sprite sp;

    bool isDead;
};

#endif // MAPACTIONS_H
