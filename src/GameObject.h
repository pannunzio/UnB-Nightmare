/*
 * GameObject.h
 *
 *  Created on: 18 de mar de 2016
 *      Author: Caio
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "Rect.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Sound.h"


class GameObject {
public:
	GameObject();
	virtual  ~GameObject();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual bool Is(std::string type) = 0;
	virtual void NotifyCollision(GameObject* other) = 0;

	virtual void StopSound() = 0;

	int layer; // 1 = subsolo , 2 = terreo , 3 = mesaniggno
	int subLayer; // 0 = nao colide com nada, 1 = baixo, 2 = meio ,3 = topo, 4 = todos
	Rect box;
	float rotation;
};

#endif /* GAMEOBJECT_H_ */
