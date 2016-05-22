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
	Bullet(float x, float y, float speed, string sprite, int frameCount	,float frameTime, bool targetsPlayer, std::string type);


	~Bullet();
	bool IsDead();
	void Update(float dt);
	void Render();

	bool Is(std::string type);


	void NotifyCollision(GameObject* other);
	bool targetsPlayer;
private:
	Sprite sp;
	float distanceLeft;
	float speed;
	std::string type; // Coffe, Bullet

};

#endif /* BULLET_H_ */
