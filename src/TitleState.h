#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "Text.h"
#include "Timer.h"
#include "Animation.h"
#include "Sound.h"
#include "Menu.h"
#include "StageState.h"
#include "Game.h"

#define BG_IMAGE            "img/telainicial.png"
#define CUTSCENE_IMAGE      "img/cutscene.png"
#define CUTSCENE_FRAMES     8
#define CUTSCENE_FTIME      2

#define MENU_POSX           250
#define MENU_POSY           350
#define MENU_SPACEMENT      50
#define MENU_TEXT_START     "Start"
#define MENU_TEXT_QUIT      "Quit Game"

#define MUSIC_TEMA_TERREO   "audio/tematerreo_main.ogg"
#define MUSIC_TEMA_MENU     "audio/menu.ogg"


class TitleState : public State{
public:
	TitleState();
	~TitleState();
    void LoadAssets();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	Sprite cutscene;
	Menu menu;
    bool isPlayingCutscene;
	void HandleInputs();

	Timer timer;

    Sound music;
	enum{
        MENU_START,
        MENU_QUIT,
        MENU_INSTRUCT
	};
};

#endif
