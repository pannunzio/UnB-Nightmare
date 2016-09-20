#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "Text.h"
#include "Timer.h"
#include "Animation.h"
#include "Sound.h"

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

    Sound music;

	int option;
	enum{
	    MENU_MIN,
        MENU_START,
        MENU_QUIT,
        MENU_MAX
	};
	Text* option1;
	Text* option2;
};

#endif
