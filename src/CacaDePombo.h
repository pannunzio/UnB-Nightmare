#ifndef CACADEPOMBO_H
#define CACADEPOMBO_H

#include "GameObject.h"
#include "Sprite.h"

class CacaDePombo: public GameObject{
public:
	CacaDePombo(float x, float y, string sprite, int frameCount,float frameTime, bool targetsPlayer, float x2, float y2, float s);
	~CacaDePombo();

	bool IsDead();
	void Update(float dt);
	void Render();

	bool Is(std::string type);

	void SetSubLayer(int subLayer);
	void NotifyCollision(GameObject* other);
	bool targetsPlayer;
	void StopSound();

private:
	Sprite sp;
	float distanceLeft;
	float distanceLimit;
    Vec2 speed;
    float gravidade;
	std::string type;
    Rect Sbox;
    float speedP;
    Sound colisaoPlayer;
};

#endif // CACADEPOMBO_H
