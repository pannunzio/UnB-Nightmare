#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <sstream>

#include "GameObject.h"
#include "Timer.h"
#include "Clock.h"
#include "Text.h"
#include "Sound.h"

#include "Game.h"
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Defines.h"


/******
    Player Defines
******/
#define PLAYER_TYPE "Player"

#define RUNNING_SPRITE        "img/Running.png"
#define RUNNING_FRAMES       6
#define RUNNING_FTIME        0.09
#define RUNNING_ACC          1.5
#define RUNNING_SLOW_SPEED   4
#define RUNNING_SPEED        5


#define STOPPING_SPRITE     "img/derrota.png"
#define STOPPING_FRAMES     12
#define STOPPING_TIMES      1

#define SKATING_SPRITE      "img/skating.png"
#define SKATING_FRAMES      3
#define SKATING_SPEED       7
#define SKATING_TIME        5
#define SKATING_MUS         "audio/skate.ogg"
#define SKATING_BASEX_INC   100

#define EATING_FILE         "img/eating.png"
#define EATING_FRAMES       6
#define EATING_SPEED
#define EATING_TIME         3

#define PLAYER_MANIFEST_INC     30

#define DELTA_ACCEPT 5

#define TEXT_FONT_FILE  "font/ComicNeue_Bold.otf"
#define TEXT_INIT       "Coffee: 0"

enum PowerUp{
	NONE,
	SKATE,
	DASH,
	COMIDA,
	CACA_DE_POMBO
};

enum MovementState{
    RUNNING,
    EATING,
    STOPPING,
    SKATING
};

enum InputState{
    NO_INPUT,
    GOING_UP,
    GOING_DOWN,
    GOING_UPSTAIRS,
    GOING_DOWNSTAIRS,
};

enum SurpriseType{
    NO_SURPRISE,
    MANIFESTACAO,
    PELADAO
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

    static Player& GetInstance();//isso aqui n�o faz sentido. Se eu tenho GetInstance(),
    static Player* player;       //n�o tem pq o ponteiro de player ser public

	void SetMaxSpeed(float maxSpeed);
    float GetSpeed();
	float GetAcceleration();
	void SetAcceleration(float acceleration);

	void Shoot();

	static int coffee_ammo; // caso pegue cafe, tem q aumentar isso aki
    MovementState movementState;
    InputState inputState;
    //temporario
    int GetBaseX();
	//Favor nao tirar o getX ele ta sendo usado por deus e o mundo agora
	int GetX();
	int GetY();
	bool isPlayerColliding();
	bool IsInPosition();
	void TimeOver();
	bool IsPlayerAlive();

    bool IsSurprise();
    void OffSurprise();
    SurpriseType GetSurpriseType();
    void SetSurpriseType();
    float GetAddTime();
    int ballonRender;
    bool GetSwitchFloor();

private:
    //Existencia do player
    bool playerAlive;
    //Atributos de posi��o
	int baseX;              //Posicao padrao
	bool isRightPosition;   //Flag de corretude da posi��o

	//Atributos de velocidade
	float speed;            //velocidade atual
	float maxSpeed;         //velocidade a alcan�ar
	float lastSpeed;        //velocidade medida no loop anterior
	float acceleration;     //aceleracao

    //Atributos de PowerUp
	PowerUp powerUp;        //Possiveis estados
	Timer itemTimer;       //Cron�metro
    bool isIndestructible;  //Flag especial atribuida por um estado
    Sound powerupMusic;
	bool isPlayingMusic;

	bool switchFloor;
	bool isSwitchingFloors;

    //Atributos de Colis�o
    bool isColliding;
    bool isPassingMapObject;

    //Indicador de fim de tempo
    bool timeOver;
    bool playerControl;

    //controla atributos surpresa
    bool isSurprise;
    SurpriseType surpriseType;

    //controla obstaculos de tempo
    float addTime;

	void checkPosition(float diff);
	void SetSpriteScale();
	bool IsIndestructible();
	void ChangeSpriteSheet(string file, int frameCount, int times = 0);

    void PlayerStops();
    void MoveGirl();
    void MoveSameFloor();       //executa o mmovimentos principais de input
    void MoveThroughFloors();   //Confere se o player pode ou nao subir/descer escada

    void SetPositionInY();

    void EndPowerUp();

    void UpdatePowerUp(float dt);
    void UpdateSpeed(float dt);

    void UpdatePosition(float dt);

    void StopIndestructiblePowerup();
    void SetNewSpeedAndPowerup(PowerUp powerup, float newSpeed, float maxSpeed);

    /**
        DEBUG
    **/
    void MagicButtons();
};

#endif /* PLAYER_H_ */
