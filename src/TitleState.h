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
<<<<<<< HEAD
#include "Animation.h"
=======
>>>>>>> 928b9815c55b70c15331b0bffb7f570355c91044

class TitleState : public State{
public:
	TitleState();
	void Update(float dt);
	void Render();


	void Pause();
	void Resume();


private:
	Sprite bg;

	Sprite cutscene;

	Timer timer;

	int option;
	Text* option1;
	Text* option2;

	Music menuMusic;

};

#endif /* TITLESTATE_H_ */
