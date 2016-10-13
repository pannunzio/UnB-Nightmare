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
//#include "Menu.h"

using std::string;
using std::cout;
using std::endl;

class State {
public:
	State();
	virtual ~State();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void LoadAssets() = 0;

	void virtual Pause() = 0;
	void virtual Resume() = 0;

	bool QuitRequested();
	bool PopRequested();

	virtual void AddObject(GameObject* ptr);

protected:

	void virtual UpdateArray(float dt);
	void virtual RenderArray();
	void virtual HandleInputs() = 0;
	//Menu menu;

	bool popRequested;
	bool quitRequested;

	std::vector<std::unique_ptr<GameObject>> objectArray;

private:
};

#endif
