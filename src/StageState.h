/*
 * State.h
 *
 *  Created on: 12 de mar de 2016
 *      Author: Caio
 */

#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include "Sprite.h"
#include "GameObject.h"
#include "State.h"
#include <iostream>
#include <vector>
#include <memory>
#include "InputManager.h"
#include "Music.h"
#include "StateData.h"
#include "Clock.h"

#include "TileMap.h"
#include "TileSet.h"
class StageState : public State{
public:
	StageState();
	~StageState();
	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
	void AddObject(GameObject* ptr);

private:
	TileSet*  tileSet;
	TileMap tileMap;
	std::vector<std::unique_ptr<GameObject>> objectArray;
	Sprite bg; // background
//	Music music;
	StateData stateData;
	Clock clock;
};

#endif /* STATE_H_ */
