#include "TitleState.h"

TitleState::TitleState()//:
//                            bg(BG_IMAGE),
//                          cutscene(CUTSCENE_IMAGE, CUTSCENE_FRAMES, CUTSCENE_FTIME),
//                          menu(MENU_POSX, MENU_POSY, MENU_SPACEMENT)
{
	this->popRequested = false;
	this->quitRequested = false;
//    this->menu.AddMenuOption(MENU_TEXT_START);
//    this->menu.AddMenuOption(MENU_TEXT_QUIT);
//
//    this->music = Sound(SOUND_ALL_CHANNELS);
//    this->music.Open(MUSIC_TEMA_TERREO, SOUND_CHANNEL_1);
//    this->music.Open(MUSIC_TEMA_MENU, SOUND_CHANNEL_1);
//    this->music.Play(SOUND_PLAY_INFINITY);
}

TitleState::~TitleState(){
    std::cout << "titlestate destroyed"<< endl;
    this->music.Stop();
}

void TitleState::LoadAssets(){
    cout << endl << "load Assets TITLESTATE" << endl << endl;
    this->bg.Open(BG_IMAGE);

    this->cutscene.Open(CUTSCENE_IMAGE);
    this->cutscene.SetFrameCount(CUTSCENE_FRAMES);
    this->cutscene.SetFrameTime(CUTSCENE_FTIME);

    this->menu = Menu(MENU_POSX, MENU_POSY, MENU_SPACEMENT);
    this->menu.AddMenuOption(MENU_TEXT_START);
    this->menu.AddMenuOption(MENU_TEXT_QUIT);

    this->music = Sound(SOUND_ALL_CHANNELS);
//    this->music.Open(MUSIC_TEMA_TERREO, SOUND_CHANNEL_1);
    this->music.Open(MUSIC_TEMA_MENU, SOUND_CHANNEL_1);
    this->music.Play(SOUND_PLAY_INFINITY);
}

void TitleState::Update(float dt){
    this->cutscene.Update(dt);
    this->timer.Update(dt);
    this->menu.Update(dt);
    HandleInputs();
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
