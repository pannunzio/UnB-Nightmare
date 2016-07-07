/*
 * TitleState.h
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "Text.h"
#include "Timer.h"
#include "Music.h"

class TitleState : public State{
public:
	TitleState();
	void Update(float dt);
	void Render();


	void Pause();
	void Resume();
private:
	Sprite bg;
	Sprite logo;
	Timer timer;

	int option;
	Text* option1;
	Text* option2;

	Music menuMusic;

};

#endif /* TITLESTATE_H_ */
