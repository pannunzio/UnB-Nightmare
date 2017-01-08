#ifndef CACADEPOMBO_H
#define CACADEPOMBO_H

#include <math.h>

#include "GameObject.h"
#include "Sprite.h"
#include "Game.h"
#include "Defines.h"
#include "Camera.h"
#include "Player.h"

#define CACA_SPRITE     "img/cacaPombo.png"
#define CACA_FRAMETIME  0.9
#define CACA_FRAMECOUNT 9

class CacaDePombo: public GameObject{
public:
	CacaDePombo(float originX, float originY);
	~CacaDePombo();

	void Update(float dt);
	void Render();
	bool IsDead();
    void NotifyCollision(GameObject* other);
	bool Is(std::string type);
    int GetLayer();
	int GetSublayer();

private:
	Sprite sp;
	float distanceLeft;
	float distanceLimit;
    Vec2 speed;
    float gravidade;
	std::string type;
	bool isExplosion;
	bool animationOver;
//    Rect Sbox;
//    float speedP;
    Sound colisaoPlayer;
};

#endif
