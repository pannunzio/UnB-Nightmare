#include "EndState.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Text.h"
#include "TitleState.h"

EndState::EndState(StateData stateData):menu(500, 350, 50){
//	this->option = 1;
//	this->option1 = new Text("font/ComicNeue_Bold.otf", 35, SOLID, "Restart", TEXT_WHITE, 0,0 );
//	this->option2 = new Text("font/ComicNeue_Bold.otf", 35, SOLID, "Quit Game", TEXT_WHITE, 0,0);
//
//	this->option1->SetPos(500,350,true,false);
//	this->option2->SetPos(500,400,true,false);
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

//	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
//		this->option--;
//
//		if(this->option < END_MIN_OPTIONS)
//			this->option = END_MAX_OPTIONS;
//	}
//
//	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
//		this->option++;
//
//		if(this->option > END_MAX_OPTIONS)
//			this->option = END_MIN_OPTIONS;
//	}
//
//	// start
//	if(this->option == 1){
//		this->option1->SetColor(TEXT_GREEN);
//
//		if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
//			Game::GetInstance().Push(new StageState());
//	}
//	else {
//		this->option1->SetColor(TEXT_WHITE);
//	}
//
//    // quit
//	if(this->option == 2){
//		this->option2->SetColor(TEXT_GREEN);
//
//		if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
//			this->quitRequested = true;
//	}
//    else {
//		this->option2->SetColor(TEXT_WHITE);
//    }
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
