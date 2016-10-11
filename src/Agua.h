#ifndef AGUA_H_
#define AGUA_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Obstacle.h"
#include "Camera.h"
#include "Defines.h"
#include "StageState.h"
#include "Game.h"
#include "Player.h"


class Agua : public GameObject {
public:
	Agua(int layer, int subLayer);
	~Agua();

	void Update(float dt);
	void Render();
    bool IsDead();
    void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	int GetLayer();
	int GetSublayer();


private:

	Sprite sp;
	float speed;
	bool isDead;
	Timer timer;
	Timer deadTimer;

};

#endif
