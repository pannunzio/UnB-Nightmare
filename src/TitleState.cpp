#include "TitleState.h"

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

TitleState::TitleState() {
	this->popRequested = false;
	this->quitRequested = false;
	this->isPlayingCutscene = true;
	this->bg.SetFile(TS_BG_IMAGE);
	this->menu = Menu(TS_MENU_POSX, TS_MENU_POSY, TS_MENU_SPACEMENT);
    this->menu.AddMenuOption(TS_MENU_TEXT_START);
    this->menu.AddMenuOption(TS_MENU_TEXT_QUIT);
    this->menu.AddMenuOption(TS_MENU_TEXT_INSTRUCTIONS);
    this->cutscene.SetFile(TS_CUTSCENE_IMAGE);
}

TitleState::~TitleState(){
    this->music.Stop();
    Resources::ClearFonts();
    Resources::ClearImages();
    Resources::ClearSound();
    DEBUG_PRINT("titlestate destroyed")
}

void TitleState::LoadAssets(){
    DEBUG_PRINT("load Assets TITLESTATE")
    this->bg.Load();
    this->menu.Load();
    this->cutscene.Load();
    this->cutscene.SetFrameCount(TS_CUTSCENE_FRAMES);
    this->cutscene.SetFrameTime(TS_CUTSCENE_FTIME);
    //this->cutscene = Sprite(TS_CUTSCENE_IMAGE, TS_CUTSCENE_FRAMES, TS_CUTSCENE_FTIME);
    this->cutscene.SetAnimationTimes(1);

//    this->music = Sound(SOUND_ALL_CHANNELS);
//    this->music.Open(TS_MUSIC_TEMA_MENU, SOUND_CHANNEL_1);
    this->music.Open("audio/subsolo_main.ogg");
    this->music.Open("audio/tematerreo_vitoria.ogg");
    this->music.Open("audio/tematerreo_main.ogg");

    this->music.Open(TS_MUSIC_TEMA_MENU);
    this->music.Play(SOUND_PLAY_INFINITY);
}

void TitleState::Update(float dt){
    this->timer.Update(dt);
    if(this->isPlayingCutscene){
        this->cutscene.Update(dt);
        if(this->cutscene.IsAnimationFinished())
            this->isPlayingCutscene = false;
    }

    if(!this->isPlayingCutscene){
        this->menu.Update(dt);
        if(menu.GetSelection()){
            switch(menu.GetSelectedOption()){
                case MENU_START:
                    this->popRequested = true;
                    Game::GetInstance().Push(new StageState());
                    break;
                case MENU_QUIT:
                    this->popRequested = true;
                    this->quitRequested = true;
                    break;
                case MENU_INSTRUCT:
                    this->popRequested = true;
                    Game::GetInstance().Push(new InstructionState());
                default:
                    cout << "selectedOption: " << menu.GetSelectedOption() << endl;
            }
        }
    }

    HandleInputs();
}

void TitleState::Render(){
	this->timer.Update(Game::GetInstance().GetDeltaTime());
	this->bg.Render(0,0);
	this->menu.Render();
    if(this->isPlayingCutscene)
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

    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
        this->isPlayingCutscene = false;
    }
	/***
        Botões Mágicos
    ***/
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

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
