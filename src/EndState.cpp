#include "EndState.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
        #define DEBUG_ONLY(x) do{x;}while(0);
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
        #define DEBUG_ONLY(x) //do{;}while(0)
#endif //DEBUG

EndState::EndState(){;
    this->isVictoryScreen = true; // stateData.playerVictory;
    this->menu = Menu(500, 350, 50);
    this->menu.AddMenuOption("Restart");
    this->menu.AddMenuOption("Quit Game");
    this->bg.SetFile(BG_FILE);
    this->derrota.SetFile("img/derrota.png");
    this->derrota.SetFrameCount(12);
    this->derrota.SetFrameTime(0.2);
}

EndState::~EndState(){
    this->music.Stop();
    DEBUG_PRINT("ENDSTATE DESTROYED")
}

void EndState::LoadAssets(){
    DEBUG_PRINT("load Assets ENDSTATE ")
    this->menu.Load();
    if(this->isVictoryScreen){
        this->bg.Load(BG_FILE);
        this->music.Open("audio/tematerreo_vitoria.ogg");
	} else {
        this->derrota.Load();
        this->bg.Load(BG_FILE);
        this->music.Open("audio/tematerreo_desespero.ogg");
	}

	this->music.Play(-1);
}

void EndState::Update(float dt){
	if(!this->isVictoryScreen)
        this->derrota.Update(dt);

	this->HandleInputs();
	this->menu.Update(dt);
	if(menu.GetSelection()){
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

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
