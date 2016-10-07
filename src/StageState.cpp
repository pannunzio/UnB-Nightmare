#include <iostream>
#include "StageState.h"
#include "Acai.h"

StageState::StageState() : tileMap(TILE_MAP_FILE, tileSet), bg(BG_FILE), menu(500, 350, 50){

	Camera::pos = Vec2(INIT_CAMERA_X,INIT_CAMERA_Y);

	this->popRequested = false;
	this->quitRequested = false; // iniciando o valor como falso

	this->tileSet = new TileSet(TILESET_WIDTH, TILESET_HEIGHT, TILE_SET_FILE);
	this->tileMap.SetTileSet(tileSet);

    this->music = Sound(-1);
    this->music.Open(INIT_MUSIC_FILE, 1);
    this->music.Play(10);

	AddObject(new Player(INIT_PLAYER_X, INIT_PLAYER_Y));

    this->spawn = 0;
    this->lixo = 0;
	this->clock.SetTime(STAGE_DURATION);
	this->waitEnd = WAIT_END_DURATION;

	//esse 200 e o player position
	this->mapLength = ((tileMap.GetWidth()-3)*TILESET_WIDTH) - 200;
	this->pause = false;
	this->menu.AddMenuOption("Resume Game");
    this->menu.AddMenuOption("Restart");
    this->menu.AddMenuOption("Quit Game");
	Camera::Resume();
}

StageState::~StageState(){
	// limpando o vector
	this->mapActionList.mapActions.clear();
	objectArray.clear();
	this->music.Stop();
	Player::player = nullptr;
	cout << "StageState destroyed" << endl;
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

        UpdateObjectArray(dt);
        CheckMapActionsPosition(dt);

        this->cooldownTimer.Update(dt);
        SpawnNewItem();
//        SpawnNewStaticObstacle();
//        SpawnNewDynamicObstacle();
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
                    break;
            }
        }
    }
}
void StageState::Pause(){
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

	this->clock.Render();
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
        cout << "not player" << endl;
    	SetEndOfGame(false);
    	return;
    }

    //se o usuario solicitar o fim do jogo ele encerra também
    if(InputManager::GetInstance().QuitRequested())
		this->quitRequested = true;

	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY))
		SetEndOfGame(false);

	//testa se o tempo acabou
    if(this->clock.GetTime() < 0.5){
        this->clock.SetTime(0);
        this->clock.StopClock();
        Player::player->TimeOver();
        if(waitEnd < 0){
            SetEndOfGame(false);
        }
    }

    if(Camera::pos.x > this->mapLength){
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
                                                    objectArray[i]->rotation*M_PI/180,
                                                    objectArray[j]->rotation*M_PI/180))){
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
        if(Player::player != nullptr &&
           Collision::IsColliding(Player::player->box,
                                  this->mapActionList.mapActions[i].box,
                                  Player::player->rotation,
                                  this->mapActionList.mapActions[i].rotation)){

            Player::player->NotifyCollision(&mapActionList.mapActions[i]);
        }
	}
}

void StageState::SpawnNewItem(){
//    if(this->clock.GetSeconds1()%3 == 0){
    if(rand()%5 > 3){
        AddObject(new Acai(3, 2));
//        if(this->spawn == 0 && rand()%100 <= 80){
//            if(rand()%3 ==1)
//                 AddObject(new Item(Player::player->layer, rand()%3+1, "COFFEE"));
//            else if(rand()%3 ==2)
//                 AddObject(new Item(Player::player->layer, rand()%3+1, "SKATE"));
//            else
//                 AddObject(new Item(Player::player->layer, rand()%3+1, "GGLIKO"));

//        }
//        this->spawn = 1;
//    }
//    else if(this->spawn != 0){
//        this->spawn = 0;
    }
}

void StageState::SpawnNewStaticObstacle(){
//	respawn das coisas

    if((1256 * this->lixo) < Camera::pos.x){
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
            if(random > 50 )
                AddObject(new Pessoa());
            else
                AddObject(new PessoaZumbi());
    	}

    	if(rand()%100 <= 5){
            AddObject(new NonCollidingPerson());
        }

    	if(rand()%100 <=5){
    		AddObject(new Manifestacao());
    	}

    	if(Player::player->layer ==  LAYER_TOP){
            if(rand()%100 < 5){
                AddObjectStatic(new Pombo());
            }
    	}
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
        Camera::Pause();
    }

    if(InputManager::GetInstance().KeyPress(SDLK_1)){
        this->clock.AddTimeToTime(10);
    }
}
