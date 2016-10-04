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

class EndState : public State{
public:
	EndState(StateData stateData);
	~EndState();
	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	Sprite derrota;
	Sound sound;
    Menu menu;
	//menu
//	int option;
//	Text* option1;
//	Text* option2;
    enum{
        MENU_RESTART,
        MENU_QUIT
    };
    void HandleInputs();

};

#endif /* ENDSTATE_H_ */
