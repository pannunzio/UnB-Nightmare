/*
 * TitleState.cpp
 *
 *  Created on: 13 de mai de 2016
 *      Author: Caio
 */

#include "TitleState.h"
#include "StageState.h"
#include "Text.h"

#include "Game.h"
TitleState::TitleState() : bg("img/title.jpg"), logo("img/logo.png"),
		text("font/Call me maybe.ttf",50,SOLID,"Press SPACE BAR to start",TEXT_BLACK, 0, 0){
	popRequested = quitRequested = false;
	text.SetPos(500,500,true,false);
	text.SetColor(SDL_Color{42,220,206});
}


void TitleState::Update(float dt){

	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
		Game::GetInstance().Push(new StageState);
	}


}
void TitleState::Render(){
	timer.Update(Game::GetInstance().GetDeltaTime());


	bg.Render(0,0);
	logo.Render(320,100); // fazer funcao de renderizar no centro
	if(timer.Get() < 2)
		text.Render(0,0);
	if(timer.Get() > 2.5)
		timer.Restart();
}
void TitleState::Pause(){

}
void TitleState::Resume(){

}


