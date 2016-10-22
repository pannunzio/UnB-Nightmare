#include "StageState.h"

StageState::StageState(){
    cout << "enter construtor STAGESTATE" << endl;
	this->popRequested = false;
	this->quitRequested = false; // iniciando o valor como falso

	this->pause = false;
	this->stagePositionX = INIT_STAGE_X;
	this->stagePositionY = INIT_STAGE_Y;
	this->spawn = 0;
    this->lixo = 0;
	this->clock.SetTime(STAGE_DURATION);
	this->waitEnd = WAIT_END_DURATION;

    Camera::pos = Vec2(stagePositionX,stagePositionY);
	Camera::Resume();
	cout << "exit contrutor STAGESTATE" << endl;
}

StageState::~StageState(){
    Resources::ClearFonts();
    Resources::ClearImages();
    Resources::ClearSound();
	// limpando o vector
//	this->mapActionList.mapActions.clear();
//	objectArray.clear();
//	this->music.Stop();
//	Player::player = nullptr;
}

void StageState::LoadAssets(){
    cout << "START of load assets STAGESTATE" << endl << endl;

    this->hud = Hud();
    this->hud.InitHud();

    cout << "back to SS load assets" << endl;

    AddObject(new Player(INIT_PLAYER_X, INIT_PLAYER_Y));
	this->layer = Player::GetInstance().GetLayer();

    cout << "Added player" << endl;

    this->menu = Menu(STAGE_STATE_MENU_POSITION_X, STAGE_STATE_MENU_POSITION_Y, STAGE_STATE_MENU_SPACEMENT);
    this->menu.AddMenuOption("Resume Game");
    this->menu.AddMenuOption("Restart");
    this->menu.AddMenuOption("Quit Game");

    cout << "Added menu" << endl;

    this->bg.Open(BG_FILE);

    cout << "Added BG" << endl;

	this->tileSet = new TileSet(TILESET_WIDTH, TILESET_HEIGHT, TILE_SET_FILE);
    this->tileMap.Load(TILE_MAP_FILE);
	this->tileMap.SetTileSet(tileSet);
	this->mapLength = ((tileMap.GetWidth()-3)*TILESET_WIDTH) - 200;

    cout << "Map Init OK" << endl;

    this->music = Sound(-1);
    this->music.Open(INIT_MUSIC_FILE, 1);
    this->music.Play(10);
    cout << "music OK" << endl;
    Resources::PrintAllLoadedResources();
}

bool StageState::GetPause(){
    return pause;
}

void StageState::Update(float dt){
    if(pause == false){
        CheckEndOfGame();
        HandleInputs();

        this->clock.Update(dt);
        if(this->clock.GetTime() == 0) waitEnd -= dt;
        if(!Player::player) MoveCamera(dt);

        UpdateObjectArray(dt);
        CheckMapActionsPosition(dt);

        this->cooldownTimer.Update(dt);
        SpawnNewItem();
        SpawnNewStaticObstacle();
        SpawnNewDynamicObstacle();

        UpdateHud(dt);
    }else{
        this->menu.Update(dt);
        if(this->menu.GetSelection()){
            switch(menu.GetSelectedOption()){
                case RESUME:
                    pause = false;
                    Camera::Resume();
                    break;
                case RESTART:
                    //RestartStage();
                    break;
                case QUIT_GAME:
                    this->popRequested = true;
                    Game::GetInstance().Push(new TitleState());
                    break;
            }
        }
    }
}
void StageState::Pause(){
}

void StageState::MoveCamera(float dt){
    cout << "Camera sob controle do StageState" << endl;
}

void StageState::Resume(){
    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
        pause = false;
        Camera::Resume();
    }
}

void StageState::Render(){
    Camera::Update(Game::GetInstance().GetDeltaTime());
	//chamando o render de cada gameObject
	this->bg.Render(0, 0);
	this->tileMap.RenderLayer(0, Camera::pos.x,Camera::pos.y);
	if(pause == true) this->menu.Render();

    RenderSubLayer(3);
    RenderSubLayer(2);
    RenderSubLayer(1);
    RenderSubLayer(0);

    this->hud.Render();
//	this->clock.Render();
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
void StageState::CheckEndOfGame(){
    //Se o player não existir, encerra o jogo
    if(!Player::player){
        this->mapActionList.mapActions.clear();
        objectArray.clear();
    	SetEndOfGame(false);
    	return;
    }

    //se o usuario solicitar o fim do jogo ele encerra também
    if(InputManager::GetInstance().QuitRequested()){
		this->quitRequested = true;
    }
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		SetEndOfGame(false);
    }

	//testa se o tempo acabou
    if(this->clock.GetTime() < 0.5){
        this->clock.SetTime(0);
        this->clock.StopClock();
        Player::GetInstance().TimeOver();
        if(waitEnd < 0){
            SetEndOfGame(false);
        }
    }

    if(Camera::pos.x > this->mapLength){
        cout << "camera pos set end of game\n\tmap length: " << this->mapLength << endl;
        cout << "\tcamera pos:  " << Camera::pos.x << endl;
        SetEndOfGame(true);
    }
}

void StageState::SetEndOfGame(bool playerVictory){
    this->stateData.timeleft = clock.GetTime();
    this->stateData.playerVictory = playerVictory;
    this->popRequested =  true;
    Game::GetInstance().Push(new EndState(stateData));
}

//Atualiza o array de Objectos e confere quais objectos 'morreram'
void StageState::UpdateObjectArray(float dt){
    //obs: NAO USAR O UPDATE ARRAY DO STATE!!!!
    for(unsigned int i = 0 ; i < objectArray.size(); i++){
    	objectArray[i]->Update(dt);
    	//checando colisisao
		for(unsigned int j = 0; j < objectArray.size(); j++){
            if((objectArray[i]->GetLayer() == objectArray[j]->GetLayer()) && (objectArray[i]->GetSublayer() == objectArray[j]->GetSublayer())){
                if(j!=i && (Collision::IsColliding( objectArray[i]->box,
                                                    objectArray[j]->box,
                                                    objectArray[i]->rotation*My_PI/180,
                                                    objectArray[j]->rotation*My_PI/180))){
                    objectArray[j]->NotifyCollision(objectArray[i].get());
                }
            }
		}

		if(objectArray[i]->IsDead()){
		   objectArray.erase (objectArray.begin() + i);
		   i--;
		}
    }
}

//Verifica se o Player está passando na frente de algum objeto de mapa como as escadas, por exemplo
void StageState::CheckMapActionsPosition(float dt){
    for(int i = mapActionList.mapActions.size() - 1; i >= 0; i--) {

        if(Player::GetInstance().IsPlayerAlive() &&
           Collision::IsColliding(Player::GetInstance().box,
                                  this->mapActionList.mapActions[i].box,
                                  Player::GetInstance().rotation,
                                  this->mapActionList.mapActions[i].rotation)){

            Player::GetInstance().NotifyCollision(&mapActionList.mapActions[i]);
        }
	}
}

void StageState::SpawnNewItem(){
    if(this->clock.GetSeconds1()%3 == 0){
        int spawner = rand()%100;
        if(this->spawn == 0 && spawner <= 80){
            spawner = spawner%4; //spawner is arbitrary value to be set only after game is being balanced
            switch(spawner){
            case 0:{
                AddObject(new SurpriseItem(Player::GetInstance().GetLayer(), rand()%3 + 1));
                cout << "added new surprise item" << endl;
                break;
            }
            case 1:{
                AddObject(new Acai(Player::GetInstance().GetLayer(), rand()%3 + 1));
                cout << "Added new acai" << endl;
                break;
            }
            case 2:{
                AddObject(new Skate(Player::GetInstance().GetLayer(), rand()%3 + 1));
                cout << "Added new skate" << endl;
                break;
            }
            case 3:{
                AddObject(new Cafe(Player::GetInstance().GetLayer(), rand()%3 + 1));
                cout << "added new cafe" << endl;
                break;
            }
            case 4:
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
//	respawn das coisas

    //numero magico??????
    if((1256 * this->lixo) < Camera::pos.x){
        cout << "spawning new trash" << endl;
        AddObjectStatic(new Lixeira(LAYER_TOP));
        AddObjectStatic(new Lixeira(LAYER_MIDDLE));
        AddObjectStatic(new Lixeira(LAYER_BOTTON));
        this->lixo++;
    }

    if(rand()%1000 <= 43){
        //INUNDACAO!
    }
}

void StageState::SpawnNewDynamicObstacle(){
    if(this->cooldownTimer.GetCurrentTime() > 0.3){ // repete a cada meio segundo
    	this->cooldownTimer.Restart();

        int random = rand()%100;
    	if(random > 30){
            if(random > 50 ){
                cout << "new pessoa" << endl;
                AddObject(new Pessoa());
            }
            else {
                cout << "new zombie" << endl;
                AddObject(new PessoaZumbi());
            }
    	}

//    	if(rand()%100 <= 5){
//            cout << "new peladao" << endl;
//            AddObject(new NonCollidingPerson());
//        }
//
//    	if(rand()%100 <=5){
//            cout << "new manifestacao" << endl;
//    		AddObject(new Manifestacao());
//    	}

    	if(Player::GetInstance().GetLayer() ==  LAYER_TOP){
            if(rand()%100 < 5){
                AddObjectStatic(new Pombo());
            }
    	}
    }

    if(Player::GetInstance().IsSurprise()){
        if(Player::GetInstance().GetSurpriseType() == MANIFESTACAO)
            AddObject(new Manifestacao());
        else if (Player::GetInstance().GetSurpriseType() == PELADAO)
            AddObject(new NonCollidingPerson());
    }
}

void StageState::UpdateHud(float dt){
    this->hud.SetClock(this->clock.GetText());
    this->hud.SetCoffeeAmmo(Player::GetInstance().coffee_ammo);

    float percentual = (100 * Player::GetInstance().GetX()) / (this->mapLength);
    this->hud.SetDistanceRun(percentual);

    this->hud.Update(dt);
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

    if(InputManager::GetInstance().KeyPress(SDLK_1)){
        this->clock.AddTimeToTime(10);
    }
}
