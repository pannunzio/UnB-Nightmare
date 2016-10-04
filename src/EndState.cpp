#include "EndState.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Text.h"
#include "TitleState.h"

EndState::EndState(StateData stateData):menu(500, 350, 50){
    this->menu.AddMenuOption("Restart");
    this->menu.AddMenuOption("Quit Game");

    this->sound = Sound(-1);

	if(stateData.playerVictory){
        this->bg = Sprite("img/cerrado.jpg");
        this->sound.Open("audio/tematerreo_vitoria.ogg");
	}

	else {
        this->derrota = Sprite("img/derrota.png", 12,0.2);
        this->bg = Sprite("img/cerrado.jpg");
        this->sound.Open("audio/tematerreo_desespero.ogg");
	}

	this->sound.Play(-1);
}

EndState::~EndState(){
    this->sound.Stop();
}

void EndState::Update(float dt){
	this->derrota.Update(dt);
	this->HandleInputs();
	this->menu.Update(dt);
	if(menu.GetSelectedOption() != -1){
            switch(menu.GetSelectedOption()){
                case MENU_RESTART:
                    this->popRequested = true;
                    Game::GetInstance().Push(new StageState());
                    break;
                case MENU_QUIT:
                    this->popRequested = true;
                    this->quitRequested = true;
                    break;
            }
    }
}

void EndState::Render(){
	this->bg.Render(0,0);
	this->derrota.Render(300,300);
	this->menu.Render();

//    this->option1->Render(0, 0);
//    this->option2->Render(0, 0);
}

void EndState::Pause(){
}

void EndState::Resume(){
}

void EndState::HandleInputs(){
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        this->popRequested = true;
		this->quitRequested = true;
	}
}
