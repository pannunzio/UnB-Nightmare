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
#include "Timer.h"

class Obstacle : public GameObject{
public:
	Obstacle();
	Obstacle(float speed,bool canBlock,std::string obstacleName, std::string sprite, int frameCount, float frameTime); // normais

	// que setam subalyer e later
	Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime,
			int layer, int subLayer);

    Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime, int layer);
	~Obstacle();

	bool IsDead();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);


private:
	std::string obstacleName;
    bool isDead;

	bool canBlock;
	int speed;
	Sprite sp;

    Sound captureSound;
    bool isSoundHappening;
};

#endif /* OBSTACLE_H_ */
