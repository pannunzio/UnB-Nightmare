#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Rect.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Sound.h"

class GameObject {
public:
    GameObject(){};
    virtual ~GameObject() {};

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual void NotifyCollision(GameObject* other) = 0;
	virtual bool Is(std::string type) = 0;

	virtual int GetLayer() = 0;
	virtual int GetSublayer() = 0;
    // 1 = subsolo , 2 = terreo , 3 = mesaniggno
	int layer;
	 // 0 = nao colide com nada, 1 = baixo, 2 = meio ,3 = topo, 4 = todos
	int subLayer;

	Rect box;
	float rotation;
};

#endif
