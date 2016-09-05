#include "EndState.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Text.h"
#include "TitleState.h"

EndState::EndState(StateData stateData){
	this->option = 1;
	this->option1 = new Text("font/ComicNeue_Bold.otf", 35, SOLID, "Restart", TEXT_WHITE, 0,0 );
	this->option2 = new Text("font/ComicNeue_Bold.otf", 35, SOLID, "Quit Game", TEXT_WHITE, 0,0);

	this->option1->SetPos(500,350,true,false);
	this->option2->SetPos(500,400,true,false);

    this->sound.SetVolume(0);

	if(stateData.playerVictory){
        this->bg = Sprite("img/cerrado.jpg");
	}

	else {
        this->derrota = Sprite("img/derrota.png", 12,0.2);
        this->bg = Sprite("img/cerrado.jpg");
	}
}

EndState::~EndState(){

}

void EndState::Update(float dt){
	this->derrota.Update(dt);

	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
		this->option--;

		if(this->option < END_MIN_OPTIONS)
			this->option = END_MAX_OPTIONS;
	}

	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
		this->option++;

		if(this->option > END_MAX_OPTIONS)
			this->option = END_MIN_OPTIONS;
	}

	// start
	if(this->option == 1){
		this->option1->SetColor(TEXT_GREEN);

		if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
			Game::GetInstance().Push(new StageState());
	}
	else {
		this->option1->SetColor(TEXT_WHITE);
	}

    // quit
	if(this->option == 2){
		this->option2->SetColor(TEXT_GREEN);

		if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
			this->quitRequested = true;
	}
    else {
		this->option2->SetColor(TEXT_WHITE);
    }
}

void EndState::Render(){
	this->bg.Render(0,0);
	this->derrota.Render(300,300);

    this->option1->Render(0, 0);
    this->option2->Render(0, 0);
}

void EndState::Pause(){
}

void EndState::Resume(){
}
