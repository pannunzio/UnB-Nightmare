#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Defines.h"
#include "Camera.h"

using std::string;

#define DEFAULT_OBSTACLE_DISTANCE 400

class Obstacle : public GameObject{
public:
    Obstacle();
    void Update(float dt);
	bool IsDead();
    void OpenSound(string fileName);
    void SetSpriteScale();
    void ChangeSpritesheet(string fileName, int frameCount, float frameTime);
    void SetHeight();
    int GetSpeed();

    int layer;
    int subLayer;

    //Sprite sp;
	bool canBlock;
	float speed;
    bool isDead;

    bool isSoundPlaying;
    Sound spriteSound;
};

#endif
