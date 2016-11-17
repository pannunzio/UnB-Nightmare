#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Player.h"
#include "Defines.h"
#include "Camera.h"

using std::string;

#define DEFAULT_OBSTACLE_DISTANCE 200

class Obstacle : public GameObject{
public:
    Obstacle();
    void Update(float dt);
	bool IsDead();
    void OpenSound(string fileName);
    void ChangeSpritesheet(string fileName, int frameCount, float frameTime);
    void SetHeight();
    int GetSpeed();

    int layer;
    int subLayer;

    //Sprite sp;
	bool canBlock;
	int speed;
    bool isDead;

    bool isSoundPlaying;
    Sound spriteSound;
};

#endif
