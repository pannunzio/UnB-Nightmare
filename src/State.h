/*
 * State.h
 *
 *  Created on: 12 de mar de 2016
 *      Author: Caio
 */

#ifndef STATE_H_
#define STATE_H_

#include "Sprite.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include <memory>
#include "InputManager.h"

#include "TileMap.h"
#include "TileSet.h"
class State {
public:
	State();
	virtual ~State();
	bool QuitRequested();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	void virtual Pause() = 0;
	void virtual Resume() = 0;


	virtual void AddObject(GameObject* ptr);

	bool PopRequested();

protected:
	void virtual UpdateArray(float dt);
	void virtual RenderArray();
	bool popRequested;
	bool quitRequested;
	std::vector<std::unique_ptr<GameObject>> objectArray;

private:



};

#endif /* STATE_H_ */
