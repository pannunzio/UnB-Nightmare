#include "TitleState.h"
#include "StageState.h"
#include "Text.h"
#include "Animation.h"
#include "Game.h"

TitleState::TitleState(): bg("img/telainicial.png"), cutscene("img/cutscene.png", 8, 2) {
	this->popRequested = false;
	this->quitRequested = false;

	this->option = MENU_START;

	this->option1 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Start", TEXT_BLACK, 0,0 );
	this->option2 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Quit Game", TEXT_BLACK, 0,0 );

	this->option1->SetPos(500,350,true,false);
	this->option2->SetPos(500,400,true,false);

    this->music = Sound(-1);
    this->music.Open("audio/tematerreo_main.ogg");
    this->music.Open("audio/menu.ogg");
    this->music.Play(-1);
}

TitleState::~TitleState(){
    std::cout << "titlestate destroyed"<< endl;
    this->music.Stop();
}

void TitleState::Update(float dt){
    this->cutscene.Update(dt);
    this->timer.Update(dt);

	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        this->popRequested = true;
		this->quitRequested = true;
	}

	// Menu Input
	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
		this->option--;
		//cout << option << endl;
		if(this->option < MENU_MIN || this->option == MENU_MIN)
			this->option = MENU_MAX - 1;
	}

	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
		this->option++;
		//cout << this->option << endl;
		if(this->option > MENU_MAX || this->option == MENU_MAX)
			this->option = MENU_MIN + 1;
	}

	// Menu Select
	switch(option){
	    case MENU_START:
            this->option1->SetColor(TEXT_WHITE);
            this->option1->SetStyle(SHADED);
            this->option2->SetColor(TEXT_BLACK);
            this->option2->SetStyle(BLENDED);

            if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
                this->popRequested = true;
                Game::GetInstance().Push(new StageState());
            }
            break;
        case MENU_QUIT:
            this->option2->SetColor(TEXT_WHITE);
            this->option2->SetStyle(SHADED);
            this->option1->SetColor(TEXT_BLACK);
            this->option1->SetStyle(BLENDED);

            if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
                this->popRequested = true;
                this->quitRequested = true;
            }
            break;
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
