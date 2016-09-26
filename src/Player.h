#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Timer.h"
#include "Clock.h"
#include "Text.h"
#include "Sound.h"

enum PowerUp{
	NONE,
	SKATE,
	DASH,
	COMIDA,
	CACA_DE_POMBO
};

enum MovementState{
    RUNNING,
    GOING_UP,
    GOING_DOWN,
    STOPPING
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
	int GetLayer();
	int GetSublayer();

    Player& GetInstance();

	bool IsTargetSpeed(float targetSpeed);
	void SetTargetSpeed(float targetSpeed);
    float GetSpeed();
	float GetAcceleration();
	void SetAcceleration(float acceleration);

	bool IsRightPosition(); // checa se ta numa posicao na qual a camera pode voltar ao normal;

	void Shoot();

	static Player* player;
	static int coffee_ammo; // caso pegue cafe, tem q aumentar isso aki
    MovementState movementState;

    //temporario
    int getBaseX();
	int getX();
	bool isPlayerColliding();
	bool isInPosition();
	float getPositionIncrement();
	void TimeOver();

private:
	void RenderHud();
	void SetSpriteScale();
	bool IsIndestructible();
	void ChangeSpriteSheet(string file, int frameCount, int times = 0);

    void Movement();
    //cuida para a sub layer ficar dentro de 1 e 3
    void CheckSublayerBoudaries();
    //executa o mmovimento
    void MovementInput();
    //Confere se o player pode ou nao subir/descer escada
    void CheckUserLayerInput();
    void SetPositionInY();

    //retorna true se encerrar o powerup
    bool EndPowerupEffect(int maxTime);

    void CheckEndPowerupEffects(float dt);
    void CheckCollisionToResetSpeed();
    void AdjustSpeed(float dt);

    //ajusta a posição do Player de acordo com o tipo do movimento
    //(se ele se desloca de um lado para o outro ou de cima para baixo)
    void SetPositionToMovementState(float dt);

    //ajusta a posição do player quando troca de andar
    void AdjustGoingUpOrDown();

    void StopIndestructiblePowerup();
    void SetNewSpeedAndPowerup(PowerUp powerup, float newSpeed, float targetSpeed);

	Sprite sp; // sprite
	float speed; // velocidade
	float acceleration; // acceleratcao
	float targetSpeed;
	Vec2 pos; // posicao atual para facilitar calculos

	PowerUp powerUp;// enumaration de powerup

	Text hud;

	Timer itemEffect;

    bool isColliding;
    bool wasColliding;
	bool isRightPosition;
    bool isPassingMapObject;
	bool isIndestructible;
	bool timeOver;


	Sound powerupMusic;
	bool isPlayingMusic;

	//temporario

	int baseX;
	float positionIncrement;
	void setPositionIncrement(float dt);
	void checkPosition(float diff);
};

#endif /* PLAYER_H_ */
