#ifndef BULLET_H_
#define BULLET_H_

#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"

class Bullet : public GameObject{
public:
	Bullet(float x, float y, float speed, string sprite, int frameCount	,float frameTime, bool targetsPlayer, std::string type);
	~Bullet();
	void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
    void NotifyCollision(GameObject* other);

	void SetLayers(int layer, int subLayer);
	void StopSound();

	bool targetsPlayer;

private:
	Sprite sp;
	float distanceLeft;
	float speed;
	std::string type; // Coffe, Bullet

    Sound shooterSound;
};

#endif /* BULLET_H_ */
