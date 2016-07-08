/*
 * Agua.h
 *
 *  Created on: 7 de jul de 2016
 *      Author: Caio
 */

#ifndef AGUA_H_
#define AGUA_H_


#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"



class Agua : public GameObject {
public:
	Agua(int layer, int subLayer);
	~Agua();

	bool IsDead();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);
private:
	Sprite sp;
	float speed;
	bool isDead;
	Timer timer;
	Timer deadTimer;

};

#endif /* AGUA_H_ */
