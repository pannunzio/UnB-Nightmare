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
void EndState::Update(float dt){
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
			popRequested = true;
			Game::GetInstance().Push(new StageState);
			Pause();
	}


}

void EndState::Render(){
	bg.Render(0,0);
	instruction.Render(0,0);
}

void EndState::Pause(){


}

void EndState::Resume(){

}
EndState::EndState(StateData stateData){
	if(stateData.playerVictory){
		music = Music("audio/endStateWin.ogg");
		bg = Sprite("img/win.jpg");
		instruction = Text("font/Call me maybe.ttf",60,SOLID,"Press SPACE BAR to start over",TEXT_GREEN, 200, 500);

	}
	else{
		music = Music("audio/endStateLose.ogg");
		bg = Sprite("img/lose.jpg");
		instruction = Text("font/Call me maybe.ttf",60,SOLID,"Press SPACE BAR to start over",TEXT_RED, 200, 500);
	}
	music.Play(-1);
}
EndState::~EndState(){

}
