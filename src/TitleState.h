#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "Text.h"
#include "Timer.h"
#include "Animation.h"
#include "Sound.h"
#include "Music.h"
#include "Menu.h"
#include "StageState.h"
#include "Game.h"

#define TS_BG_IMAGE            "img/telainicialC.jpg"
#define TS_CUTSCENE_IMAGE      "img/cutscene.png"
#define TS_CUTSCENE_FRAMES     8
#define TS_CUTSCENE_FTIME      2

#define TS_MENU_POSX                250
#define TS_MENU_POSY                350
#define TS_MENU_SPACEMENT           50
#define TS_MENU_TEXT_START          "Start"
#define TS_MENU_TEXT_QUIT           "Quit Game"
#define TS_MENU_TEXT_INSTRUCTIONS   "Instructions"

#define TS_MUSIC_TEMA_TERREO   "audio/menu.aiff"
#define TS_MUSIC_TEMA_MENU     "audio/menu.aiff"


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

    //Sound music;
    Music music;

	enum{
        MENU_START,
        MENU_QUIT,
        MENU_INSTRUCT
	};
};

#endif
