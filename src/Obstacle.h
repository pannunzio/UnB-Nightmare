#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

using std::string;

class Obstacle : public GameObject{
public:

    void Update(float dt);
	bool IsDead();
    void OpenSound(string fileName);
    void ChangeSpritesheet(string fileName, int frameCount, float frameTime);

    int layer;
    int subLayer;

    Sprite sp;
	bool canBlock;
	int speed;
    bool isDead;
    Sound spriteSound;
};

#endif
