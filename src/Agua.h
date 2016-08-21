#ifndef AGUA_H_
#define AGUA_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Agua : public GameObject {
public:
	Agua(int layer, int subLayer);
	~Agua();

	void Update(float dt);
	void Render();
    bool IsDead();
    void NotifyCollision(GameObject* other);
	bool Is(std::string type);

	void StopSound();

private:

	Sprite sp;
	float speed;
	bool isDead;
	Timer timer;
	Timer deadTimer;

};

#endif
