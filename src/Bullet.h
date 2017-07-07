#ifndef BULLET_H_
#define BULLET_H_

#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Camera.h"
#include "Game.h"
#include "Defines.h"
#include "Player.h"

#define BULLET_MAX_DISTANCE 1000
#define BULLET_SPRITE       "img/coffee.png"
#define BULLET_FRAMECOUNT   9
#define BULLET_FRAMETIME    0.3


class Bullet : public GameObject{
public:
	Bullet(float originX, float originY);
	~Bullet();
	void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
    void NotifyCollision(GameObject* other);
    int GetLayer();
	int GetSublayer();

private:
	Sprite sp;
	float distanceLeft;
	float speed;
    Sound shooterSound;
};

#endif /* BULLET_H_ */
