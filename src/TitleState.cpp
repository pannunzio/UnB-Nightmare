#include "TitleState.h"
#include "StageState.h"
#include "Text.h"
#include "Animation.h"
#include "Game.h"

TitleState::TitleState(): bg("img/telainicial.png"), cutscene("img/cutscene.png", 8, 2), menu(500, 350, 50) {
	this->popRequested = false;
	this->quitRequested = false;
    this->menu.AddMenuOption("Start");
    this->menu.AddMenuOption("Quit Game");
//	this->option = MENU_START;

//	this->option1 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Start", TEXT_BLACK, 0,0 );
//	this->option2 = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, "Quit Game", TEXT_BLACK, 0,0 );

//	this->option1->SetPos(500,350,true,false);
//	this->option2->SetPos(500,400,true,false);

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
    this->menu.Update(dt);
    HandleInputs();
    if(menu.GetSelection()){
            switch(menu.GetSelectedOption()){
                case MENU_START:
                    //this->popRequested = true;
                    Game::GetInstance().Push(new StageState());
                    break;
                case MENU_QUIT:
                    this->popRequested = true;
                    this->quitRequested = true;
                    break;
                default:
                    cout << "selectedOption: " << menu.GetSelectedOption() << endl;
            }
    }
}

void TitleState::Render(){
	this->timer.Update(Game::GetInstance().GetDeltaTime());
	this->bg.Render(0,0);
	this->menu.Render();
    if(this->timer.GetCurrentTime() < 32)
    	this->cutscene.Render(0,0);
}

void TitleState::Pause(){
}

void TitleState::Resume(){
}

void TitleState::HandleInputs(){
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
        this->popRequested = true;
		this->quitRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(SDLK_p)){
        this->bg.Open("img/telainicialPB.jpg");
	}
	if(InputManager::GetInstance().KeyPress(SDLK_c)){
        this->bg.Open("img/telainicialC.jpg");
	}
	if(InputManager::GetInstance().KeyPress(SDLK_s)){
        this->bg.Open("img/telainicial.png");
	}
}
