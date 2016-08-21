#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "GameObject.h"
#include "Timer.h"

class Animation : public GameObject{
public:
	Animation(float x, float y, float rotation, std::string sp, int frameCount, float frameTime, bool ends);

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);

private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
	Sprite sp;

};

#endif
