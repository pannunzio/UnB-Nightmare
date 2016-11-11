#include "InstructionState.h"

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

InstructionState::InstructionState(){
    DEBUG_PRINT("enter construtor InstructionState")
	SetInitialStateValues();
	this->instruction = "Pressione Enter para começar";

	DEBUG_PRINT("exit contrutor InstructionState")
}

InstructionState::~InstructionState(){
}

void InstructionState::LoadAssets(){
    DEBUG_PRINT("START of load assets InstructionState")

    this->hud = Hud();
    this->hud.InitHud();

    this->instructions = new Text("font/ComicNeue-Angular_Bold_Oblique.otf", 35, BLENDED, this->instruction, TEXT_BLACK, 15, 400);
    DEBUG_PRINT("back to SS load assets")

    AddObject(new Player(INIT_PLAYER_X, INIT_PLAYER_Y));
	this->layer = Player::GetInstance().GetLayer();

    DEBUG_PRINT("Added player")

    this->menu = Menu(INSTR_STATE_MENU_POSITION_X, 500, INSTR_STATE_MENU_SPACEMENT);
    this->menu.AddMenuOption("Start");
    this->menu.AddMenuOption("Voltar");

    DEBUG_PRINT("Added menu")

    this->bg.Open(BG_FILE);

    DEBUG_PRINT("Added BG")

	this->tileSet = new TileSet(TILESET_WIDTH, TILESET_HEIGHT, TILE_SET_FILE);
    this->tileMap.Load(TILE_MAP_FILE);
	this->tileMap.SetTileSet(tileSet);
	this->mapLength = ((tileMap.GetWidth()-3)*TILESET_WIDTH) - 200;

    DEBUG_PRINT("Map Init OK")

    this->music = Sound(-1);
    this->music.Open(INIT_MUSIC_FILE, 1);
    this->music.Play(10);
    DEBUG_PRINT("music OK")
    Resources::PrintAllLoadedResources();
}

bool InstructionState::GetPause(){
    return pause;
}

void InstructionState::Update(float dt){
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

    this->clock.AddTimeToTime(Player::GetInstance().GetAddTime());

    UpdateHud(dt);
    UpdateMenu(dt);

    this->instructions->SetText(this->instruction);
}
void InstructionState::Pause(){
}

void InstructionState::MoveCamera(float dt){
    DEBUG_PRINT("Camera sob controle do InstructionState")
}

void InstructionState::Resume(){
    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
        pause = false;
        Camera::Resume();
    }
}

void InstructionState::Render(){
    Camera::Update(Game::GetInstance().GetDeltaTime());
	//chamando o render de cada gameObject
	this->bg.Render(0, 0);
	this->tileMap.RenderLayer(0, Camera::pos.x,Camera::pos.y);

    RenderSubLayer(3);
    RenderSubLayer(2);
    RenderSubLayer(1);
    RenderSubLayer(0);

    this->hud.Render();
//    if(pause == true)
    this->menu.Render();


    this->instructions->Render(0, 0);
//	this->clock.Render();
}

//Add game object
void InstructionState::AddObject(GameObject* ptr){
	objectArray.emplace_back(ptr);
}

void InstructionState::AddObjectStatic(GameObject* ptr){
	objectArray.emplace(objectArray.begin() ,ptr);
}

/*
    FUNCOES AUXILIARES AO JOGO !!!

    |  |  |
    V  V  V
*/

void InstructionState::SetInitialStateValues(){
    this->popRequested = false;
	this->quitRequested = false; // iniciando o valor como falso

	this->pause = false;
	this->stagePositionX = INIT_STAGE_X;
	this->stagePositionY = INIT_STAGE_Y;
	this->spawn = 0;
    this->lixo = 0;
	this->clock.SetTime(STAGE_DURATION);
	this->waitEnd = WAIT_END_DURATION;
	this->gameEnd = false;
	this->showInstruction = false;

    Camera::pos = Vec2(stagePositionX,stagePositionY);
	Camera::Resume();
}

//verifica se o jogo acabou
void InstructionState::CheckEndOfGame(){
    //Se o player não existir, encerra o jogo
    if(!Player::player){
        this->mapActionList.mapActions.clear();
        objectArray.clear();
        this->popRequested =  true;
        Game::GetInstance().Push(new StageState());
    	return;
    }

    //se o usuario solicitar o fim do jogo ele encerra também
    if(InputManager::GetInstance().QuitRequested()){
		this->quitRequested = true;
		this->gameEnd = true;
    }
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
//		SetEndOfGame(false);
    }

	//testa se o tempo acabou
    if(this->clock.GetTime() < 0.5){
        std::stringstream segundosRestantes;
        segundosRestantes << "Vai começar o jogo em " << (int) waitEnd;
        this->instruction = segundosRestantes.str();
        this->clock.SetTime(0);
        this->clock.StopClock();
        Player::GetInstance().TimeOver();
        if(waitEnd < 0){
            this->popRequested =  true;
            Game::GetInstance().Push(new StageState());
        }
    }

    if(Camera::pos.x > this->mapLength){
        DEBUG_PRINT("camera pos set end of game\n\tmap length: " << this->mapLength)
        DEBUG_PRINT("\tcamera pos:  " << Camera::pos.x)
        SetEndOfGame(true);
    }
}

void InstructionState::SetEndOfGame(bool playerVictory){
}

//Atualiza o array de Objectos e confere quais objectos 'morreram'
void InstructionState::UpdateObjectArray(float dt){
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

                    if(objectArray[i]->Is("Player")){

                        if((objectArray[j]->Is("Lixeira")
                             || objectArray[j]->Is("Pessoa")
                             || objectArray[j]->Is("Zumbi")
                             || objectArray[j]->Is("Lixeira"))) {
                            this->instruction = "Desvie apertando S ou W !";
                        }

                        if(objectArray[j]->Is("Manifestacao")){
                            this->instruction = "Aperte D para atravessar!";
                        }

                        if(objectArray[j]->Is("Zumbi")){
                            this->instruction = "Aperte ESPACO para atirar café no zumbi!";
                        }
                    }
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
void InstructionState::CheckMapActionsPosition(float dt){
    for(int i = mapActionList.mapActions.size() - 1; i >= 0; i--) {

        if(Player::GetInstance().IsPlayerAlive() &&
           Collision::IsColliding(Player::GetInstance().box,
                                  this->mapActionList.mapActions[i].box,
                                  Player::GetInstance().rotation,
                                  this->mapActionList.mapActions[i].rotation)){

            Player::GetInstance().NotifyCollision(&mapActionList.mapActions[i]);
            this->instruction = "Pressione as SETAS ^ ou v para subir/descer Escadas!";
        }

	}
}

void InstructionState::SpawnNewItem(){
    if(this->clock.GetSeconds1()%3 == 0){
        int spawner = rand()%100;
        if(this->spawn == 0 && spawner <= 80){
            spawner = spawner%5; //spawner is arbitrary value to be set only after game is being balanced
            switch(spawner){
            case 0:{
                AddObject(new SurpriseItem(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT("added new surprise item")
                break;
            }
            case 1:{
                AddObject(new Acai(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT("Added new acai")
                break;
            }
            case 2:{
                AddObject(new Skate(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT("Added new skate")
                break;
            }
            case 3:{
                AddObject(new Cafe(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT("added new cafe")
                break;
            }
            case 4:
                AddObject(new ClockItem(Player::GetInstance().GetLayer(), rand()%3 + 1));
                DEBUG_PRINT("added new clock ")
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

void InstructionState::SpawnNewStaticObstacle(){
//	respawn das coisas

    //numero magico??????
    if((1256 * this->lixo) < Camera::pos.x){
        DEBUG_PRINT("spawning new trash")
        AddObjectStatic(new Lixeira(LAYER_TOP));
        AddObjectStatic(new Lixeira(LAYER_MIDDLE));
        AddObjectStatic(new Lixeira(LAYER_BOTTON));
        this->lixo++;
    }

    if(rand()%1000 <= 43){
        //INUNDACAO!
    }
}

void InstructionState::SpawnNewDynamicObstacle(){
    if(this->cooldownTimer.GetCurrentTime() > 0.3){ // repete a cada meio segundo
    	this->cooldownTimer.Restart();

        int random = rand()%100;
    	if(random > 30){
            if(random > 50 ){
                DEBUG_PRINT("new pessoa")
                AddObject(new Pessoa());
            }
            else {
                DEBUG_PRINT("new zombie")
                AddObject(new PessoaZumbi());
            }
    	}

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

void InstructionState::UpdateHud(float dt){
    this->hud.SetClock(this->clock.GetText());
    this->hud.SetCoffeeAmmo(Player::GetInstance().coffee_ammo);

    float percentual = (100 * Player::GetInstance().GetX()) / (this->mapLength);
    this->hud.SetDistanceRun(percentual);

    this->hud.Update(dt);
}

void InstructionState::UpdateMenu(float dt){
    this->menu.Update(dt);
    if(this->menu.GetSelection()){
        switch(menu.GetSelectedOption()){
            case (START_GAME):
                DEBUG_PRINT("QUIT GAME")
                this->popRequested = true;
                Game::GetInstance().Push(new StageState());
                break;
            case (VOLTAR):
                this->popRequested = true;
                Game::GetInstance().Push(new TitleState());
                break;
            default:
                break;
        }
    }
}

void InstructionState::RenderSubLayer(int sublayer){
    for(unsigned int i = 0 ; i < objectArray.size(); i++) {
		if(objectArray[i]->GetSublayer() == sublayer)
            objectArray[i]->Render();
	}
}

void InstructionState::HandleInputs(){
    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
        pause = true;
    }

    if(InputManager::GetInstance().KeyPress(SDLK_1)){
        this->clock.AddTimeToTime(10);
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
