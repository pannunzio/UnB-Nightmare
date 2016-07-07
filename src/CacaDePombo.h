#ifndef CACADEPOMBO_H
#define CACADEPOMBO_H

#include "GameObject.h"
#include "Sprite.h"

class CacaDePombo: public GameObject{
public:
	CacaDePombo(float x, float y, string sprite, int frameCount,float frameTime, bool targetsPlayer);
	~CacaDePombo();

	bool IsDead();
	void Update(float dt);
	void Render();

	bool Is(std::string type);

	void SetSubLayer(int subLayer);
	void NotifyCollision(GameObject* other);
	bool targetsPlayer;

private:
	Sprite sp;
	float distanceLeft;
    Vec2 speed;
    float gravidade;
	std::string type;

    Sound colisaoPlayer;
};

#endif // CACADEPOMBO_H
