#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "Text.h"
#include "Timer.h"
#include "Music.h"
#include "Animation.h"

class TitleState : public State{
public:
	TitleState();
	~TitleState();

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
