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

class EndState : public State{
public:

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
	EndState();
	EndState(StateData stateData);
	~EndState();
private:
	Sprite bg;
	Sprite derrota;
	Sound sound;

	//menu
	int option;
	Text* option1;
	Text* option2;

};

#endif /* ENDSTATE_H_ */
