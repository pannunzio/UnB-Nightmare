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
};

#endif /* STATE_H_ */
