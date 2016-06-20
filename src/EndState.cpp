/*
 * EndState.cpp
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#include "EndState.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Text.h"
#include "TitleState.h"

void EndState::Update(float dt){
	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
		option--;
		if(option < END_MIN_OPTIONS)
			option = END_MAX_OPTIONS;
	}
	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
		option++;
		if(option > END_MAX_OPTIONS)
			option = END_MIN_OPTIONS;
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


}

void EndState::Render(){
	bg.Render(0,0);

    option1->Render(0, 0);
    option2->Render(0, 0);
}

void EndState::Pause(){


}

void EndState::Resume(){

}
EndState::EndState(StateData stateData){
	option = 1;
	option1 = new Text("font/Call me maybe.ttf", 35, SOLID, "Restart", TEXT_WHITE, 0,0 );
	option2 = new Text("font/Call me maybe.ttf", 35, SOLID, "Quit Game", TEXT_WHITE, 0,0);

	option1->SetPos(500,350,true,false);
	option2->SetPos(500,400,true,false);

	if(stateData.playerVictory){
		music = Music("audio/endStateWin.ogg");
		bg = Sprite("img/win.jpg");
		cout<<"VENCEUU"<<endl;
	}
	else{
		music = Music("audio/endStateLose.ogg");
		bg = Sprite("img/lose.jpg");
		cout<<"PERDEUUUU"<<endl;
	}
	music.Play(-1);
}
EndState::~EndState(){

}
