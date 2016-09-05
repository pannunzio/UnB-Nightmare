#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Obstacle : public GameObject{
public:
	Obstacle();
	Obstacle(float speed,bool canBlock,std::string obstacleName, std::string sprite, int frameCount, float frameTime); // normais
    Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime, int layer);
	Obstacle(float speed, bool canBlock, std::string obstacleName, std::string sprite, int frameCount, float frameTime, int layer, int subLayer);

	~Obstacle();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);

	void StopSound();

private:
    void OpenZombieSound(int num);
    void OpenXingamentoSound(int num);
    void OpenGotaSound(int num);

	std::string obstacleName;
    bool isDead;

	bool canBlock;
	int speed;
	Sprite sp;

    Sound spriteSound;
    Sound captureSound;
    bool isSoundHappening;
};

#endif /* OBSTACLE_H_ */
