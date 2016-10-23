#ifndef INSTRUCTIONSTATE_H
#define INSTRUCIONSTATE_H

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

#include "Game.h"
#include "GameObject.h"
#include "Camera.h"
#include "EndState.h"
#include "Player.h"
#include "Item.h"
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
#define TILE_MAP_FILE   "map/tileMap.txt"
#define TILE_SET_FILE   "img/tileset.png"
#define BG_FILE         "img/cerrado.jpg"

#define INIT_STAGE_X   0
#define INIT_STAGE_Y   280

#define INIT_MUSIC_FILE "audio/tematerreo_main.ogg"

#define INIT_PLAYER_X   200
#define INIT_PLAYER_Y   550

#define STAGE_DURATION      60 //em segundos
#define WAIT_END_DURATION   5

#define INSTR_STATE_MENU_POSITION_X     500
#define INSTR_STATE_MENU_POSITION_Y     350
#define INSTR_STATE_MENU_SPACEMENT      50

class InstructionState : public State{
public:
	InstructionState();
	~InstructionState();

	void LoadAssets();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
	bool GetPause();

	void AddObject(GameObject* ptr);
	void AddObjectStatic(GameObject* ptr);

private:
    void SetInitialStateValues();
    //Verifica se o jogo acabou
    void CheckEndOfGame();
    void SetEndOfGame(bool playerVictory);
    void MoveCamera(float dt);
    //Atualiza o array de Objectos e confere quais objectos 'morreram'
    void UpdateObjectArray(float dt);
    //Verifica se o Player est� passando na frente de algum objeto de mapa como as escadas, por exemplo
    void CheckMapActionsPosition(float dt);
    void SpawnNewItem();
    void SpawnNewStaticObstacle();
    void SpawnNewDynamicObstacle();
    void HandleInputs();//registra os inputs de interesse ao StageState

    void UpdateHud(float dt);
    void UpdateMenu(float dt);

    void RenderSubLayer(int sublayer);
    Menu menu;
    enum{
        START_GAME,
        VOLTAR
    };

    Text* instructions;
    bool showInstruction;
    string instruction;

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
	int mapLength;
	bool pause;
	float stagePositionX;
	float stagePositionY;
	int layer;
	bool gameEnd;

	Sound music;
};

#endif // INSTRUCTIONSTATE_H