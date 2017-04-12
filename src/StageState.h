#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include <iostream>
#include <vector>
#include <memory>

#include "Sprite.h"
#include "GameObject.h"
#include "State.h"
#include "InputManager.h"
#include "StateData.h"
#include "Clock.h"
#include "Timer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "MapActionList.h"
#include "Animation.h"
#include "Sound.h"
#include "Music.h"
#include "Game.h"
#include "GameObject.h"
#include "Camera.h"
#include "EndState.h"
#include "Player.h"
#include "Item.h"
#include "Collision.h"
#include "Defines.h"
#include "Obstacle.h"
#include "Pombo.h"
#include "Agua.h"
#include "MapActionList.h"
#include "Manifestacao.h"
#include "Pessoa.h"
#include "PessoaZumbi.h"
#include "Lixeira.h"
#include "NonCollidingPerson.h"
#include "Acai.h"
#include "Cafe.h"
#include "Skate.h"
#include "SurpriseItem.h"
#include "ClockItem.h"

#include "Hud.h"


using std::string;
using std::cout;
using std::endl;

/******
    StageState Defines
******/
#define BG_FILE         "img/cerrado.jpg"

#define INIT_STAGE_X    0
#define INIT_STAGE_Y    0

#define INIT_MUSIC_FILE "audio/terreo.ogg"//"audio/tematerreo_main.ogg"
#define SSOLO_MUSIC_FILE "audio/subsolo.ogg"

#define INIT_PLAYER_X   TILESET_WIDTH/2

#define STAGE_DURATION      74 //em segundos
#define WAIT_END_DURATION   5  //medido no olhômetro

#define STAGE_STATE_MENU_POSITION_X     500
#define STAGE_STATE_MENU_POSITION_Y     350
#define STAGE_STATE_MENU_SPACEMENT      50

//      Chances iniciais de surgir: obstaculos
#define STAGE_STATE_SPAWN_PERSON    100-70 //70% de chance
#define STAGE_STATE_SPAWN_ZOMBIE    100-50 //50% de chance
#define STAGE_STATE_SPAWN_BIRD      100-15 //05% de chance

//      Chances iniciais de surgir: itens
#define STAGE_STATE_SPAWN_TRASH     100-70 //70% de chance
#define STAGE_STATE_SPAWN_ACAI      100-50 //50% de chance
#define STAGE_STATE_SPAWN_SKATE     100-40 //40% de chance
#define STAGE_STATE_SPAWN_SURPRISE  100-40 //40% de chance
#define STAGE_STATE_SPAWN_CLOCK     100-40 //40% de chance

#define COOL_DOWN_TIME      0.5


class StageState : public State{
public:
	StageState();
	~StageState();

	void LoadAssets();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
	bool GetPause();

	void AddObject(GameObject* ptr);
	void AddObjectStatic(GameObject* ptr);

private:
    void ResetState();
    //Verifica se o jogo acabou
    void CheckEndOfGame(float dt);
    void SetEndOfGame(bool playerVictory);
    void MoveCamera(float dt);
    //Atualiza o array de Objectos e confere quais objectos 'morreram'
    void UpdateObjectArray(float dt);
    //Verifica se o Player está passando na frente de algum objeto de mapa como as escadas, por exemplo
    void CheckMapActionsPosition(float dt);
    void SpawnNewItem();
    void SpawnNewStaticObstacle();
    void SpawnNewDynamicObstacle();
    void HandleInputs();//registra os inputs de interesse ao StageState

    void UpdateHud(float dt);
    void UpdateMenu(float dt);

    void MusicController();

    void RenderSubLayer(int sublayer);
    Menu menu;
    enum{
        RESUME,
        RESTART,
        QUIT_GAME
    };
    enum{
        SURPRISE,
        ACAI,
        SKATE,
        CAFE,
        CLOCK,
        ITEM_TOTAL
    };
	TileSet*  tileSet;
	TileMap tileMap;
	std::vector<std::unique_ptr<GameObject>> objectArray;
	MapActionList mapActionList;
	Sprite bg; // background
    StateData stateData;
	Clock clock;
	float waitEnd;

    Hud hud;

	Timer cooldownTimer;
	int spawn;
	int lixo;
	bool pause;
	int layer;
	bool gameEnd;
//	Sound music;
    Music music;

    /**
        Map builders
    **/
    int mapLength;
    float stagePositionX;
	float stagePositionY;
	int layerTopHeight;
	int layerMiddleHeight;
	int layerBottonHeight;

	/**
        Spawn builders
	**/
	//      Obstaculos
	int spawnPerson;
	int spawnZombie;
	int spawnBird;
	int spawnTrash;
	//      Itens
	int spawnSkate;
	int spawnAcai;
	int spawnSurprise;
	int spawnClock;


	/**
        DEBUG
	**/
	void MagicButtons();
};

#endif
