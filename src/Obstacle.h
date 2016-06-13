/*
 * Obstacle.h
 *
 *  Created on: 13 de jun de 2016
 *      Author: Caio
 */

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "GameObject.h"
#include "Sprite.h"

class Obstacle : public GameObject{
public:

	Obstacle(int speed, float spawnRate, bool canBlock,std::string obstacleName, int frameCount, float frameTime);
	~Obstacle();

	bool IsDead();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);

private:
	std::string obstacleName;
	float spawnRate; // em porcentagem
	bool canBlock;


	Timer cooldownTimer;

	int speed;
	Sprite sp;

};

#endif /* OBSTACLE_H_ */
