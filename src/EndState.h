/*
 * EndState.h
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#ifndef ENDSTATE_H_
#define ENDSTATE_H_

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "StateData.h"
#include "Menu.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "TitleState.h"

class EndState : public State{
public:
	EndState(StateData stateData);
	~EndState();
	void LoadAssets();
	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	Sprite derrota;
	Sound sound;

	bool isVictoryScreen;

    Menu menu;
    enum{
        MENU_RESTART,
        MENU_QUIT
    };
    void HandleInputs();
};

#endif /* ENDSTATE_H_ */
