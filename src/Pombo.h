#ifndef POMBO_H
#define POMBO_H

#include "GameObject.h"
#include "Sprite.h"
#include "Obstacle.h"
#include "Player.h"
#include "Game.h"
#include "CacaDePombo.h"
#include "Camera.h"

class Pombo: public Obstacle{
public:
    Pombo();
    ~Pombo();

    void Update(float dt);
    void Render();
	void NotifyCollision(GameObject* other);
	bool Is(string type);
    int GetLayer();
    int GetSublayer();

    int layer;
    int subLayer;
private:
    void FazCaca();
    bool fazendoCaca;
};

#endif
