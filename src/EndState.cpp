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
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		popRequested = true;
		Game::GetInstance().Push(new TitleState);
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
		instruction = Text("font/Call Me Maybe.ttf",20,SOLID,"Press SPACE BAR to start over or ESC to return to Main Menu",TEXT_GREEN, 50, 500);

	}
	else{
		music = Music("audio/endStateLose.ogg");
		bg = Sprite("img/lose.jpg");
		instruction = Text("font/Call Me Maybe.ttf",25,SOLID,"Press SPACE BAR to start over or ESC to return to Main Menu",TEXT_RED, 50, 500);
	}
	music.Play(-1);
}
EndState::~EndState(){

}
