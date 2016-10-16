#include "EndState.h"

EndState::EndState(StateData stateData){
    this->isVictoryScreen = stateData.playerVictory;
}

EndState::~EndState(){
    this->sound.Stop();
    cout << "ENDSTATE DESTROYED" << endl;
}

void EndState::LoadAssets(){
    cout << "load Assets ENDSTATE " << endl << endl;
    this->menu = Menu(500, 350, 50);
    this->menu.AddMenuOption("Restart");
    this->menu.AddMenuOption("Quit Game");

    if(this->isVictoryScreen){
        this->bg = Sprite("img/cerrado.jpg");
        this->sound.Open("audio/tematerreo_vitoria.ogg", 1);
	} else {
        this->derrota = Sprite("img/derrota.png", 12,0.2);
        this->bg = Sprite("img/cerrado.jpg");
        this->sound.Open("audio/tematerreo_desespero.ogg", 1);
	}

	this->sound.Play(-1);
}

void EndState::Update(float dt){
	this->derrota.Update(dt);
	this->HandleInputs();
	this->menu.Update(dt);
	if(menu.GetSelection()){
            switch(menu.GetSelectedOption()){
                case MENU_RESTART:
                    this->popRequested = true;
//                    Game::GetInstance().Push(new StageState());
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
	if(!this->isVictoryScreen)
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
