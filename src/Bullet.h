/*
 * Bullet.h
 *
 *  Created on: 31 de mar de 2016
 *      Author: Caio
 */

#ifndef BULLET_H_
#define BULLET_H_
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"

class Bullet : public GameObject{
public:
	Bullet(float x, float y, float angle, float speed, float maxDistance, string sprite, int frameCount
			,float frameTime, bool targetsPlayer);


	~Bullet();
	bool IsDead();
	void Update(float dt);
	void Render();

	bool Is(std::string type);


	void NotifyCollision(GameObject* other);
	bool targetsPlayer;
private:
	Sprite sp;
	Vec2 speed;
	float distanceLeft;

};

#endif /* BULLET_H_ */
