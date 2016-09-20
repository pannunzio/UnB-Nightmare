#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include "Sprite.h"
#include "GameObject.h"
#include "State.h"
#include <iostream>
#include <vector>
#include <memory>
#include "InputManager.h"
#include "StateData.h"
#include "Clock.h"
#include "Timer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "MapActionList.h"
#include "Animation.h"
#include "Sound.h"

using std::string;
using std::cout;
using std::endl;

class StageState : public State{
public:
	StageState();
	~StageState();
	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

	void AddObject(GameObject* ptr);
	void AddObjectStatic(GameObject* ptr);

private:
    //Verifica se o jogo acabou
    void CheckEndOfGame();
    void SetEndOfGame(bool playerVictory);
    //Atualiza o array de Objectos e confere quais objectos 'morreram'
    void UpdateObjectArray(float dt);
    //Verifica se o Player está passando na frente de algum objeto de mapa como as escadas, por exemplo
    void CheckMapActionsPosition(float dt);
    void SpawnNewItem();
    void SpawnNewStaticObstacle();
    void SpawnNewDynamicObstacle();

    void RenderSubLayer(int sublayer);

	TileSet*  tileSet;
	TileMap tileMap;
	std::vector<std::unique_ptr<GameObject>> objectArray;
	MapActionList mapActionList;
	Sprite bg; // background
    StateData stateData;
	Clock clock;

	Timer cooldownTimer;
	int spawn;
	int lixo;
	int mapLength;

	Sound music;
};

#endif
