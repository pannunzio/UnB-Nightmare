/*
 * TitleState.cpp
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#include "TitleState.h"
#include "StageState.h"
#include "Text.h"
#include "Animation.h"

#include "Game.h"
TitleState::TitleState() : bg("img/telainicial.png"), menuMusic("audio/menu.ogg"), cutscene("img/cutscene.png", 8,2) {
	popRequested = quitRequested = false;
	option = TITLE_MIN_OPTIONS;

    menuMusic.Play(-1);
    menuMusic.SetVolume(100);

	option1 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Start", TEXT_WHITE, 0,0 );
//	option1Selected = Text("font/Call me maybe.ttf", 35, SOLID, "Start", TEXT_GREEN, 0,0 );
	option2 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Quit Game", TEXT_WHITE, 0,0 );
//	option2Selected = Text("font/Call me maybe.ttf", 35, SOLID, "Quit Game", TEXT_GREEN, 0,0);

	option1->SetPos(500,350,true,false);
//	option1Selected.SetPos(500,350,true,false);
	option2->SetPos(500,400,true,false);
//	option2Selected.SetPos(500,400,true,false);


}


void TitleState::Update(float dt){




	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
		menuMusic.Stop();
	}


	// Menu

	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
		option--;
		cout << option << endl;
		if(option < TITLE_MIN_OPTIONS)
			option = TITLE_MAX_OPTIONS;
	}
	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
		option++;
		cout << option << endl;
		if(option > TITLE_MAX_OPTIONS)
			option = TITLE_MIN_OPTIONS;
	}

//	// start
	if(option == 1){
		option1->SetColor(TEXT_GREEN);
		if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
			Game::GetInstance().Push(new StageState());
	}
	else {
		option1->SetColor(TEXT_WHITE);
	}

    // quit
	if(option == 2){
		option2->SetColor(TEXT_GREEN);
		if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
			quitRequested = true;
	}
    else
		option2->SetColor(TEXT_WHITE);

	cutscene.Update(dt);

	timer.Update(dt);

}
void TitleState::Render(){
	timer.Update(Game::GetInstance().GetDeltaTime());

	bg.Render(0,0);
    option1->Render(0, 0);
    option2->Render(0, 0);
    if(timer.Get()<16)
    	cutscene.Render(0,0);
}
void TitleState::Pause(){

}
void TitleState::Resume(){

}



