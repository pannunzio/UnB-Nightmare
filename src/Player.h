/*
 * Player.h
 *
 *  Created on: 18 de mai de 2016
 *      Author: apoio
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Timer.h"
#include "Clock.h"
#include "Text.h"


enum PowerUp{
	NONE,
	SKATE,
	DASH

};


class Player : public GameObject{
public:
	Player(float x,float y);
	virtual ~Player();
	void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);
	bool IsTargetSpeed(float targetSpeed);
	void SetTargetSpeed(float targetSpeed);

    Player& GetInstance();

	static Player* player;

	float GetSpeed();
	float GetAcceleration();

	void SetAcceleration(float acceleration);

	bool IsRightPosition(); // checa se ta numa posicao na qual a camera pode voltar ao normal;

	void Movement();
	void Shoot();

	static int coffee_ammo; // caso pegue cafe, tem q aumentar isso aki
private:
	Sprite sp; // sprite
	float speed; // velocidade
	float acceleration; // acceleratcao
	float targetSpeed;
	Vec2 pos; // posicao atual para facilitar calculos

	PowerUp powerUp;// enumaration de powerup

	bool isRightPosition;


};

#endif /* PLAYER_H_ */
