#include "StageState.h"

//#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
        #define DEBUG_ONLY(x) do{x;}while(0);
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
        #define DEBUG_ONLY(x) //do{;}while(0)
#endif //DEBUG

StageState::StageState(){
    DEBUG_PRINT("StageState::StageState()-begin-")
    this->menu = Menu(STAGE_STATE_MENU_POSITION_X, STAGE_STATE_MENU_POSITION_Y, STAGE_STATE_MENU_SPACEMENT);
    this->menu.AddMenuOption("Resume Game");
    this->menu.AddMenuOption("Restart");
    this->menu.AddMenuOption("Quit Game");

    ResetState();
    /**
        DEBUG
    **/
    DEBUG_PRINT("MagicButtons:")
    DEBUG_PRINT(" - Cafe:         C")
    DEBUG_PRINT(" - SurpriseItem: V")
    DEBUG_PRINT(" - Skate:        B")
    DEBUG_PRINT(" - Acai:         N")
    DEBUG_PRINT(" - CLockItem:    M")
    DEBUG_PRINT(" - Pombo:        F")
	DEBUG_PRINT(" - Manifestacao: G")
	DEBUG_PRINT(" - Zumbi:        H")
	DEBUG_PRINT(" - Pessoa:       J")
    DEBUG_PRINT(" - Lixeira:      K")
	DEBUG_PRINT("StageState::StageState()-end-")
}

void StageState::ResetState(){
    DEBUG_PRINT("StageState::ResetState()-begin-")

    //Variáveis de comunicação com a game
    this->popRequested = false;
	this->quitRequested = false;

    //Variáveis de construção do cenário
	this->stagePositionX = INIT_STAGE_X;
	this->layerTopHeight = LAYER_TOP_HEIGHT;
	this->layerMiddleHeight = LAYER_MIDDLE_HEIGHT;
	this->layerBottonHeight = LAYER_BOTTON_HEIGHT;

	//Variáves de condições de jogo
	this->clock.SetTime(STAGE_DURATION);
	this->pause = false;
	this->spawn = 0;
    this->lixo = 0;
    //      Obstaculos
    this->spawnPerson = STAGE_STATE_SPAWN_PERSON;
	this->spawnZombie = STAGE_STATE_SPAWN_ZOMBIE;
	this->spawnBird = STAGE_STATE_SPAWN_BIRD;
	this->spawnTrash = STAGE_STATE_SPAWN_TRASH;

	//      Itens
	this->spawnSkate = STAGE_STATE_SPAWN_SKATE;
	this->spawnAcai = STAGE_STATE_SPAWN_ACAI;
	this->spawnSurprise = STAGE_STATE_SPAWN_SURPRISE;
	this->spawnClock = STAGE_STATE_SPAWN_CLOCK;


	//Variáveis de finalização do StageState
	this->waitEnd = WAIT_END_DURATION;
	this->gameEnd = false;

    Camera::SetX(INIT_STAGE_X);
    Camera::SetY(INIT_STAGE_Y);

    this->music.Open(INIT_MUSIC_FILE);

	DEBUG_PRINT("StageState::ResetState()-end-")
}

StageState::~StageState(){
    this->music.Stop();
    Resources::ClearFonts();
    Resources::ClearImages();
    Resources::ClearSound();
//    Resources::ClearMusic();
	// limpando o vector
//	this->mapActionList.mapActions.clear();
//	objectArray.clear();
//	this->music.Stop();
//	Player::player = nullptr;
}

void StageState::LoadAssets(){
    DEBUG_PRINT("StageState::LoadAssets()-begin-")

//    this->music.Open("audio/subsolo_main.ogg");
//    this->music.Open("audio/tematerreo_vitoria.ogg");
//
//    this->music.Open(INIT_MUSIC_FILE);

    this->hud = Hud();
    this->hud.InitHud();

    AddObject(new Player(INIT_PLAYER_X, LAYER_MIDDLE_HEIGHT));
	this->layer = Player::GetInstance().GetLayer();
    DEBUG_PRINT(" - Added player")

    this->menu.Load();
    DEBUG_PRINT(" - Added menu")

    this->bg.Open(BG_FILE);
    DEBUG_PRINT(" - Added BG")

	this->tileSet = new TileSet(TILESET_WIDTH, TILESET_HEIGHT, TILE_SET_FILE);
    this->tileMap.Load(TILE_MAP_FILE);
	this->tileMap.SetTileSet(tileSet);
	this->mapLength = ((tileMap.GetWidth()-3)*TILESET_WIDTH) - 200;
    DEBUG_PRINT(" - Map Init OK")

//    this->music = Sound(-1);
//    this->music.Open(INIT_MUSIC_FILE, 1);
    this->music.Open(INIT_MUSIC_FILE);

//    this->music.Play(1);
    DEBUG_PRINT(" - music OK")

    Resources::PrintAllLoadedResources();

    DEBUG_PRINT("StageState::LoadAssets()-end-")
}

bool StageState::GetPause(){
    return pause;
}

void StageState::Update(float dt){
    MusicController();

    CheckEndOfGame(dt);
    if(pause == false){
        DEBUG_PRINT("StageState::Update()-begin-")
        DEBUG_ONLY(MagicButtons())
        this->clock.Update(dt);
        HandleInputs();

        UpdateObjectArray(dt);
        CheckMapActionsPosition(dt);
        this->cooldownTimer.Update(dt);
        #ifndef DEBUG
        SpawnNewItem();
        SpawnNewStaticObstacle();
        SpawnNewDynamicObstacle();
        #endif // DEBUG
        if(this->cooldownTimer.GetCurrentTime() > COOL_DOWN_TIME)
            this->cooldownTimer.Restart();

        this->clock.AddTimeToTime(Player::GetInstance().GetAddTime());

        UpdateHud(dt);
    DEBUG_PRINT("StageState::Update()-end-")
    } else {
        UpdateMenu(dt);
    }
}
void StageState::Pause(){
}

void StageState::MoveCamera(float dt){
    if(Camera::GetX()+Camera::GetWidth() < mapLength)
        Camera::MoveX(dt*100*0.5);
}

void StageState::Resume(){
    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
        pause = false;
    }
}

void StageState::Render(){
    Camera::Update(Game::GetInstance().GetDeltaTime());
	//chamando o render de cada gameObject
	this->bg.Render(0, 0);
	this->tileMap.RenderLayer(0, Camera::GetX(),Camera::GetY());

    RenderSubLayer(3);
    RenderSubLayer(2);
    RenderSubLayer(1);
    RenderSubLayer(0);

    this->hud.Render();
    if(pause == true)
        this->menu.Render();
}

//Add game object
void StageState::AddObject(GameObject* ptr){
	objectArray.emplace_back(ptr);
}

void StageState::AddObjectStatic(GameObject* ptr){
	objectArray.emplace(objectArray.begin() ,ptr);
}

/*
    FUNCOES AUXILIARES AO JOGO !!!

    |  |  |
    V  V  V
*/

//verifica se o jogo acabou
void StageState::CheckEndOfGame(float dt){
    DEBUG_PRINT("StageState::CheckEndOfGame()-begin-")
    //Se o player não existir, encerra o jogo
    if(!Player::GetInstance().IsPlayerAlive()){
        MoveCamera(dt);
        waitEnd -= dt*100;
        this->mapActionList.mapActions.clear();
    }

    //se o usuario solicitar o fim do jogo ele encerra também
    if(InputManager::GetInstance().QuitRequested()){
		this->quitRequested = true;
		this->gameEnd = true;
    }
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		SetEndOfGame(false);
    }

	//testa se o tempo acabou
    if(this->clock.GetTime() < 0.5){
        this->clock.SetTime(0);
        this->clock.StopClock();
        Player::GetInstance().TimeOver();
        waitEnd -= dt;
    }
    if(waitEnd < 0){
        //objectArray.clear();
        SetEndOfGame(false);
    }

    if(Camera::GetX() > this->mapLength){
        SetEndOfGame(true);
    }
    DEBUG_PRINT("StageState::CheckEndOfGame()-end-")
}

void StageState::SetEndOfGame(bool playerVictory){
    this->stateData.timeleft = clock.GetTime();
    this->stateData.playerVictory = playerVictory;
    if(playerVictory){
        this->popRequested =  true;
        Game::GetInstance().Push(new EndState());
    } else {
        pause = true;
    }
    this->gameEnd = true;
}

//Atualiza o array de Objectos e confere quais objectos 'morreram'
void StageState::UpdateObjectArray(float dt){
    DEBUG_PRINT("StageState::UpdateObjectArray()-begin-")
    //obs: NAO USAR O UPDATE ARRAY DO STATE!!!!
    for(unsigned int i = 0 ; i < objectArray.size(); i++){
    	//checando colisisao
		for(unsigned int j = 0; j < objectArray.size(); j++){
            if(i == j)continue;

            if((objectArray[i]->GetLayer() == objectArray[j]->GetLayer()) &&
               (objectArray[i]->GetSublayer() == objectArray[j]->GetSublayer())){
                    if(Collision::IsColliding(objectArray[i]->box, objectArray[j]->box)){
                        objectArray[j]->NotifyCollision(objectArray[i].get());
//                        DEBUG_PRINT((objectArray[j].get())->sp.GetFile() << " colidiu com " <<
//                                    (objectArray[i].get())->sp.GetFile())
                    }
            }
		}
		if(objectArray[i]->IsDead()){
		   objectArray.erase (objectArray.begin() + i);
		   i--;
		}
    }
    for(unsigned int i = 0 ; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }
    DEBUG_PRINT("StageState::UpdateObjectArray()-end-")
}

//Verifica se o Player está passando na frente de algum objeto de mapa como as escadas, por exemplo
void StageState::CheckMapActionsPosition(float dt){
	DEBUG_PRINT("StageState::CheckMapActionsPosition()-begin-")
    for(int i = mapActionList.mapActions.size() - 1; i >= 0; i--) {

        if(Player::GetInstance().IsPlayerAlive() &&
           Collision::IsColliding(Player::GetInstance().box,
                                  this->mapActionList.mapActions[i].box)){

            Player::GetInstance().NotifyCollision(&mapActionList.mapActions[i]);
        }
	}
	DEBUG_PRINT("StageState::CheckMapActionsPosition()-end-")
}

void StageState::SpawnNewItem(){
    if(this->clock.GetSeconds1()%3 == 0){
        int random = rand()%100;
        if(this->spawn == 0 && random <= 80){
            int item = random%ITEM_TOTAL; //spawner is arbitrary value to be set only after game is being balanced
            switch(item){
            case SURPRISE:{
                AddObject(new SurpriseItem(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT(" - added new surprise item")
                break;
            }
            case ACAI:{
                AddObject(new Acai(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT(" - Added new acai")
                break;
            }
            case SKATE:{
                AddObject(new Skate(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT(" - Added new skate")
                break;
            }
            case CAFE:{
                AddObject(new Cafe(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT(" - added new cafe")
                break;
            }
            case CLOCK:
                AddObject(new ClockItem(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT(" - added new clock ")
                break;
            case 5:
            default:
                break;
            } // close switch
        }
        this->spawn = 1;
    }
    else if(this->spawn != 0){
        this->spawn = 0;
    }
}

void StageState::SpawnNewStaticObstacle(){
    if(this->cooldownTimer.GetCurrentTime() > COOL_DOWN_TIME){
        if(rand()%100 > 98){
            DEBUG_PRINT(" - spawning new trash")
            AddObjectStatic(new Lixeira());
            AddObjectStatic(new Lixeira());
            this->lixo++;
        }

        if(rand()%100 > 99){
            //INUNDACAO!
        }
    }
}

void StageState::SpawnNewDynamicObstacle(){
    DEBUG_PRINT("StageState::SpawnNewDynamicObstacle()-begin-")
    if(this->cooldownTimer.GetCurrentTime() > COOL_DOWN_TIME){
        int random = rand()%100;
    	if(random > spawnPerson){
            if(random > spawnZombie){
                DEBUG_PRINT(" - new pessoa")
                AddObject(new Pessoa());
            }
            else {
                DEBUG_PRINT(" - new zombie")
                AddObject(new PessoaZumbi());
            }
    	}
        if(Player::GetInstance().GetLayer() ==  LAYER_TOP){
            if(random > spawnBird){
                AddObjectStatic(new Pombo());
            }
    	}
    }
    if(Player::GetInstance().IsSurprise()){
        if(Player::GetInstance().GetSurpriseType() == MANIFESTACAO)
            AddObject(new Manifestacao());
        else if (Player::GetInstance().GetSurpriseType() == PELADAO)
            AddObject(new NonCollidingPerson());
        Player::GetInstance().OffSurprise();
    }
    DEBUG_PRINT("StageState::SpawnNewDynamicObstacle()-end-")
}

void StageState::UpdateHud(float dt){
	DEBUG_PRINT("StageState::UpdateHud()-begin-")
    this->hud.SetClock(this->clock.GetText());
    this->hud.SetCoffeeAmmo(Player::GetInstance().coffee_ammo);

    //Player deve avisar qual balão deverá ser renderizado, hud só obedece
    if(Player::GetInstance().IsPlayerAlive()){
        this->hud.ballonX = Player::GetInstance().GetX() - Camera::GetX();
        this->hud.ballonY = Player::GetInstance().GetY() - Camera::GetY();
        this->hud.showBallon = Player::GetInstance().ballonRender;
    }else{
        this->hud.showBallon = 0;
    }

    float percentual = (100 * Player::GetInstance().GetX()) / (this->mapLength);
    this->hud.SetDistanceRun(percentual);

    this->hud.Update(dt);
    DEBUG_PRINT("StageState::UpdateHud()-end-")
}

void StageState::UpdateMenu(float dt){
    this->menu.Update(dt);
    if(this->menu.GetSelection()){
        switch(menu.GetSelectedOption()){
            case RESUME:
                pause = false;
                DEBUG_PRINT("OPTION: RESUME GAME")
                break;
            case RESTART:
                objectArray.clear();
                ResetState();
                LoadAssets();
                DEBUG_PRINT("OPTION: RESTART GAME")
                break;
            case QUIT_GAME:
                DEBUG_PRINT("OPTION: QUIT GAME")
                this->popRequested = true;
                Game::GetInstance().Push(new TitleState());
                break;
        }
    }
}

void StageState::MusicController(){
    if(!this->music.IsPlaying()){
        this->music.Play(-1);
    }
    switch(Player::GetInstance().GetLayer()){
    case LAYER_BOTTON:
        if(Player::GetInstance().GetSwitchFloor()){
            this->music.Stop();
            this->music.Open(SSOLO_MUSIC_FILE);
            this->music.Play(-1);
            std::cout << "SWITCH bottom" << std::endl;
        }
        break;
    case LAYER_MIDDLE:
        if(Player::GetInstance().GetSwitchFloor()){
            this->music.Stop();
            this->music.Open(INIT_MUSIC_FILE);
            this->music.Play(-1);
            std::cout << "SWITCH not bottom" << std::endl;
        }
        break;
    default:
        break;
    }

}

void StageState::RenderSubLayer(int sublayer){
    for(unsigned int i = 0 ; i < objectArray.size(); i++) {
		if(objectArray[i]->GetSublayer() == sublayer)
            objectArray[i]->Render();
	}
}

void StageState::HandleInputs(){
    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
        pause = true;
    }
}

/**
    DEBUG
**/
void StageState::MagicButtons(){
    if(InputManager::GetInstance().KeyPress(SDLK_v)){
        AddObject(new SurpriseItem(Player::GetInstance().GetLayer(), rand()%3 + 1));
    }
    if(InputManager::GetInstance().KeyPress(SDLK_b)){
        AddObject(new Skate(Player::GetInstance().GetLayer(), rand()%3 + 1));
    }
    if(InputManager::GetInstance().KeyPress(SDLK_n)){
        AddObject(new Acai(Player::GetInstance().GetLayer(), rand()%3 + 1));
    }
    if(InputManager::GetInstance().KeyPress(SDLK_m)){
        AddObject(new ClockItem(Player::GetInstance().GetLayer(), rand()%3 + 1));
    }
    if(InputManager::GetInstance().KeyPress(SDLK_c)){
        AddObject(new Cafe(Player::GetInstance().GetLayer(), rand()%3 + 1));
    }
    if(InputManager::GetInstance().KeyPress(SDLK_k)){
        AddObjectStatic(new Lixeira());
    }
    if(InputManager::GetInstance().KeyPress(SDLK_j)){
        AddObject(new Pessoa());
    }
    if(InputManager::GetInstance().KeyPress(SDLK_h)){
        AddObject(new PessoaZumbi());
    }
    if(InputManager::GetInstance().KeyPress(SDLK_g)){
        AddObject(new Manifestacao());
    }
    if(InputManager::GetInstance().KeyPress(SDLK_f)){
        AddObject(new Pombo());
    }
    if(InputManager::GetInstance().KeyPress(SDLK_1)){
        this->clock.AddTimeToTime(10);
    }
}
#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
