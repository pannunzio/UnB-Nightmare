#include "TitleState.h"
#include "StageState.h"
#include "Text.h"
#include "Animation.h"
#include "Game.h"

TitleState::TitleState(): bg("img/telainicial.png"), cutscene("img/cutscene.png", 8,2) {
	this->popRequested = false;
	this->quitRequested = false;

	option = TITLE_MIN_OPTIONS;

	option1 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Start", TEXT_BLACK, 0,0 );
	option2 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Quit Game", TEXT_BLACK, 0,0 );

	option1->SetPos(500,350,true,false);
	option2->SetPos(500,400,true,false);
}

TitleState::~TitleState(){

}

void TitleState::Update(float dt){

    cutscene.Update(dt);
    timer.Update(dt);


	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
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

	// start
	if(option == 1){
		option1->SetColor(TEXT_WHITE);
		option1->SetStyle(SHADED);
		option2->SetColor(TEXT_BLACK);
		option2->SetStyle(BLENDED);

		if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
			Game::GetInstance().Push(new StageState());

		}
	}

    // quit
	if(option == 2){
		option2->SetColor(TEXT_WHITE);
		option2->SetStyle(SHADED);
		option1->SetColor(TEXT_BLACK);
		option1->SetStyle(BLENDED);

		if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
			quitRequested = true;
	}
}

void TitleState::Render(){
	timer.Update(Game::GetInstance().GetDeltaTime());

	bg.Render(0,0);
    option1->Render(0, 0);
    option2->Render(0, 0);

    if(timer.Get() < 32)
    	cutscene.Render(0,0);
}

void TitleState::Pause(){
}

void TitleState::Resume(){
}



