#include "TitleState.h"
#include "StageState.h"
#include "Text.h"
#include "Animation.h"
#include "Game.h"

TitleState::TitleState(): bg("img/telainicial.png"), cutscene("img/cutscene.png", 8, 2) {
	this->popRequested = false;
	this->quitRequested = false;

	this->option = TITLE_MIN_OPTIONS;

	this->option1 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Start", TEXT_BLACK, 0,0 );
	this->option2 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Quit Game", TEXT_BLACK, 0,0 );

	this->option1->SetPos(500,350,true,false);
	this->option2->SetPos(500,400,true,false);
}

TitleState::~TitleState(){

}

void TitleState::Update(float dt){
    this->cutscene.Update(dt);
    this->timer.Update(dt);

	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		this->quitRequested = true;
	}

	// Menu
	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
		this->option--;
		cout << option << endl;
		if(this->option < TITLE_MIN_OPTIONS)
			this->option = TITLE_MAX_OPTIONS;
	}

	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
		this->option++;
		cout << this->option << endl;
		if(this->option > TITLE_MAX_OPTIONS)
			this->option = TITLE_MIN_OPTIONS;
	}

	// start
	if(this->option == 1){
		this->option1->SetColor(TEXT_WHITE);
		this->option1->SetStyle(SHADED);
		this->option2->SetColor(TEXT_BLACK);
		this->option2->SetStyle(BLENDED);

		if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
			Game::GetInstance().Push(new StageState());

		}
	}

    // quit
	if(this->option == 2){
		this->option2->SetColor(TEXT_WHITE);
		this->option2->SetStyle(SHADED);
		this->option1->SetColor(TEXT_BLACK);
		this->option1->SetStyle(BLENDED);

		if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
			this->quitRequested = true;
	}
}

void TitleState::Render(){
	this->timer.Update(Game::GetInstance().GetDeltaTime());

	this->bg.Render(0,0);
    this->option1->Render(0, 0);
    this->option2->Render(0, 0);

    if(this->timer.Get() < 32)
    	this->cutscene.Render(0,0);
}

void TitleState::Pause(){
}

void TitleState::Resume(){
}
