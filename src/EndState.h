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
#include "Music.h"
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
	Music music;
	Text instruction;
};

#endif /* ENDSTATE_H_ */
