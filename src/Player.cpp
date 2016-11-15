#include "Player.h"
#include "Obstacle.h"
#include "SurpriseItem.h"
#include "ClockItem.h"

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

Player* Player::player = nullptr;
int Player::coffee_ammo = 1;

/***
        CONSTRUTOR
***/
Player::Player(float x, float y) {
	//Inicialização da referencia a Player
	this->player = this;
    this->sp = Sprite(RUNNING_SPRITE, RUNNING_FRAMES, RUNNING_FTIME);
    //Inicialização de posição
	this->baseX = (int)x;
	this->subLayer = SUBLAYER_MIDDLE;
	this->layer = LAYER_MIDDLE;
	this->box.Centralize(x,y,sp.GetWidth(),sp.GetHeight());
	this->isRightPosition = false;
	//this->layer = rand()%3 +1;

	//inicialização de estado
	this->movementState = RUNNING;
    this->maxSpeed = speed = lastSpeed = RUNNING_SPEED;
	this->acceleration = RUNNING_ACC;
	this->inputState = NO_INPUT;
	//Inicialização de estado referente a itens
	this->powerUp = NONE;
    this->isIndestructible = false;
    this->itemTimer = Timer();
    this->coffee_ammo = 0;
    this->powerupMusic = Sound(1);
    this->isPlayingMusic = false;

    //Inicialização de conhecimentos externos
    this->timeOver = false;
    this->playerControl = true;//modificar para criar o inicio de jogo
    //Inicialização referente a colisão
    this->isColliding = false;
    this->wasColliding = false;
    this->isPassingMapObject = false;
    this->isSurprise = false;
    this->surpriseType = NO_SURPRISE;
    this->addTime = 0.0;

    //Inicialização do balão
    this->ballon = Sprite(BALLON_STAIRS, BALLON_STAIRS_FRAMES, BALLON_STAIRS_FTIME);
    this->ballonRender = false;
}

/***
        DESTRUTOR
***/
Player::~Player() {
	this->player = nullptr;
}

/***
        UPDATE
***/
void Player::Update(float dt){
	//atualiza o sprite
	this->sp.Update(dt);

	//se for o caso, atualiza o balão
	if(ballonRender)
        this->ballon.Update(dt);

    if(timeOver == true)
        PlayerStops();

    // faz os movimentos do input
    MoveGirl();

    // Atualiza o tempo e estado dos powerUps
    UpdatePowerUp(dt);

    //Atualiza a posição de acordo com o estado atual
    UpdatePosition(dt);

    //LATeR: criar uma funcao propria pra resetar esses aqui
    this->isColliding = false;
    this->isPassingMapObject = false;
    this->ballonRender = false;
    this->isSurprise = false;
    this->surpriseType = NO_SURPRISE;
    this->addTime = 0.0;
}

void Player::PlayerStops(){
    switch(movementState){
        case RUNNING:
            this->ChangeSpriteSheet(STOPPING_SPRITE, STOPPING_FRAMES, STOPPING_TIMES);
            movementState = STOPPING;
            break;
        default:
            break;
    }
    playerControl = false;
}

void Player::Render(){
	this->sp.Render((int)(this->box.x - Camera::pos.x), (int)(this->box.y - Camera::pos.y));
	this->SetSpriteScale();
	if(this->ballonRender){
        this->ballon.Render((int)(this->box.x + BALLON_POS_X - Camera::pos.x),
                            (int)(this->box.y - BALLON_POS_Y - Camera::pos.y));
	}
}

bool Player::IsDead(){
	// camera passou player
	if(Camera::pos.x + 30 > box.x + sp.GetWidth()){
		this->player = nullptr;
//		cout<<"TESTE"<<endl;
		return true;
	}
	return false; // retornar true se tiver camera passou, ou se o tempo acabou
	//isso pode ser feito pelo state data.
}

void Player::NotifyCollision(GameObject* other){
    if(other->Is("Pessoa") || other ->Is("Zumbi") || other->Is("Lixeira")){
        DEBUG_PRINT("colidiu Pessoa/Zumbi/Lixeira")
        if(!isIndestructible){
            this->isColliding = true;
            this->wasColliding = true;
            this->SetMaxSpeed(0.0);
            Obstacle* obst = (Obstacle*) other;
            this->speed = obst->GetSpeed();
        } else {
            //se estiver com um powerup que dá indestrutibilidade, desvia dos obstaculos principais
            if (this->subLayer == 3){
                this->subLayer--;
            } else if (this->subLayer == 1){
                this->subLayer++;
            }
        }
    }

    if(other->Is("Manifestacao")){
        DEBUG_PRINT("colidiu MANIFESTAÇÃO")
        StopIndestructiblePowerup();

        this->isColliding = true;
        this->wasColliding = true;
        Obstacle* obst = (Obstacle*) other;
        this->speed = obst->GetSpeed();

        // se ficar apertando vai mais rapido
        if(InputManager::GetInstance().KeyPress(SDLK_d))
        	this->box.x += 20;
        }

    if(other->Is("Cafe")){
        this->coffee_ammo++;
        DEBUG_PRINT("colidiu CAFE")
    }

    if(other->Is("Skate")){
        DEBUG_PRINT("colidiu SKATE")
        if(!this->isPlayingMusic && this->powerUp != SKATE){
            this->powerupMusic.Open(SKATING_MUS, 5);
            this->powerupMusic.Play(1);
            this->powerupMusic.SetVolume(180);
        }

        SetNewSpeedAndPowerup(PowerUp::SKATE, this->speed, SKATING_SPEED);
        this->ChangeSpriteSheet(SKATING_SPRITE, SKATING_FRAMES);
    }

    if(other->Is("Acai")){//DEBUG aperte G para ficar no estado EATING
        DEBUG_PRINT("colidiu ACAI")
        StopIndestructiblePowerup();
        SetNewSpeedAndPowerup(PowerUp::COMIDA, 3.5, RUNNING_SLOW_SPEED);
        ChangeSpriteSheet(EATING_FILE, EATING_FRAMES);
        movementState = EATING;
    }

    //caca de pombo
    if(other->Is("Caca")){
        DEBUG_PRINT("colidiu CACA")
        StopIndestructiblePowerup();
        SetNewSpeedAndPowerup(PowerUp::CACA_DE_POMBO, 3.5, RUNNING_SLOW_SPEED);
    }

    if(other->Is("Escada")){
        DEBUG_PRINT("colidiu ESCADA")
        this->isPassingMapObject = true;
        this->ballonRender = true;
    }

    if(other->Is("Agua")){
        DEBUG_PRINT("colidiu AGUA")
        StopIndestructiblePowerup();
        SetNewSpeedAndPowerup(PowerUp::NONE, 3.0, RUNNING_SLOW_SPEED);
    }
    if(other->Is("Surprise!")){
        DEBUG_PRINT("colidiu SURPRISE!")
        this->isSurprise = true;
        SurpriseItem* item = (SurpriseItem*) other;
        this->surpriseType = item->GetSurprise();
    }

    if(other->Is("NonColliding")){
        DEBUG_PRINT("nudez no campus!")
        this->speed = 2;
        this->isColliding = true;
        this->wasColliding = true;
    }

    if (other->Is("ClockItem")){
        ClockItem* item = (ClockItem*) other;
        this->addTime = item->GetTimeToAdd();
        DEBUG_PRINT("player caught clockitem: " << item->GetTimeToAdd())
    }
}

void Player::Shoot(){
	Vec2 shootPos = box.CenterPos();

	if(this->coffee_ammo > 0){
		Bullet* coffee = new Bullet(shootPos.x, shootPos.y, 10, COFFEE_FILE, 3, 0.3, false, "Coffee");
		coffee->SetLayers(this->layer, this->subLayer); // para renderizar corretamente
		Game::GetInstance().GetCurrentState().AddObject(coffee);
		coffee_ammo--;
	}
}

void Player::SetSpriteScale(){
    if(this->subLayer == 3)
    	this->sp.SetScale(0.95);
    if(this->subLayer == 2)
        this->sp.SetScale(1);
    if(this->subLayer == 1)
        this->sp.SetScale(1.05);
}

void Player::ChangeSpriteSheet(string file, int frameCount, int times){
    this->sp.Open(file);
    this->sp.SetFrameCount(frameCount);
    this->sp.SetAnimationTimes(times);
    this->sp.SetClip(this->box.x, this->box.y, this->sp.GetWidth(), this->sp.GetHeight());
}


void Player::MoveGirl(){
    if(playerControl == true){
        MoveSameFloor();
        MoveThroughFloors();
    }
    SetPositionInY();
}

//confere os comandos inseridos pelo usuario
void Player::MoveSameFloor(){
    //movimento de sublayer
	if(InputManager::GetInstance().KeyPress(SDLK_w)){
		if(this->subLayer <= 2)
			this->subLayer++;
    }

	if(InputManager::GetInstance().KeyPress(SDLK_s)){
		if(this->subLayer >= 2)
			this->subLayer--;
	}
	//atira cafe
    if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
        Shoot();

    }

    /***
    BOTOES DE DEBUG
    ***/
    if(InputManager::GetInstance().KeyPress(SDLK_o)){
        this->layer++;
    }
    if(InputManager::GetInstance().KeyPress(SDLK_l)){
        this->layer--;
    }
    if(InputManager::GetInstance().KeyPress(SDLK_g)){
        this->movementState = EATING;
    }
}

void Player::SetPositionInY(){
    if(this->layer == LAYER_TOP)
        this->box.y = LAYER_TOP_HEIGHT + 2;//230

    if(this->layer == LAYER_MIDDLE)
        this->box.y = LAYER_MIDDLE_HEIGHT;//495

    if(this->layer == LAYER_BOTTON)
        this->box.y = LAYER_BOTTON_HEIGHT;//772

    this->box.y -= (this->subLayer - 3) * 24;
}

//Confere se o player pode ou nao subir/descer escada
void Player::MoveThroughFloors(){
    if(this->powerUp != PowerUp::SKATE){
        //verifica se esta ao lado da escada
        if(this->subLayer == SUBLAYER_TOP){
            //verifica se nao esta no topo para poder subir
            if(this->layer == LAYER_MIDDLE || this->layer == LAYER_BOTTON)
                if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY) && this->isPassingMapObject){
                    this->layer++;
                    this->subLayer = SUBLAYER_TOP;
                    this->inputState = GOING_UP;
                }
            //verifica se nao esta em baixo para poder descer
            if(this->layer == LAYER_TOP|| this->layer == LAYER_MIDDLE)
                if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY) && isPassingMapObject){
                    this->layer--;
                    this->subLayer = SUBLAYER_TOP;
                    this->inputState = GOING_DOWN;
                }
        }
    }
}

void Player::UpdatePowerUp(float dt){
    switch(this->powerUp){
    case NONE:
        break;
    case SKATE:
        this->itemTimer.Update(dt);
        this->isPassingMapObject = false;
        this->isIndestructible = true;
        if (this->itemTimer.GetCurrentTime() > SKATING_TIME){
            EndPowerUp();
            this->ChangeSpriteSheet(RUNNING_SPRITE, RUNNING_FRAMES);
            this->movementState = RUNNING;
        }
        break;
    case COMIDA:
        this->itemTimer.Update(dt);
        if (this->itemTimer.GetCurrentTime() > EATING_TIME){
            EndPowerUp();
            this->ChangeSpriteSheet(RUNNING_SPRITE, RUNNING_FRAMES);
            this->movementState = RUNNING;
        }
        break;
    case CACA_DE_POMBO:
        this->itemTimer.Update(dt);
        this->EndPowerUp();
        break;
    }
}

void Player::EndPowerUp(){
    this->powerUp = NONE;
    this->SetMaxSpeed(RUNNING_SPEED);

    if(this->powerupMusic.IsPlaying())
        this->powerupMusic.Stop();

    if(this->isIndestructible){
        this->isIndestructible = false;
        this->powerUp = NONE;
        this->powerupMusic.Stop();
    }
}

void Player::CheckCollisionToResetSpeed(){
    if(!this->isColliding){
        if(this->wasColliding){
            this->speed = RUNNING_SPEED;
            this->SetMaxSpeed(RUNNING_SPEED);
            this->wasColliding = false;
        }
    }
}

void Player::UpdateSpeed(float dt){
	//v = v0 + at
	if(this->speed != this->maxSpeed){
        //lastSpeed evita que a speed fique oscilando em volta de maxSpeed
        if(this->maxSpeed > this->speed
            && this->maxSpeed > this->lastSpeed){

            this->lastSpeed = this->speed;
			this->speed += this->acceleration * dt;

		}
		else if(this->maxSpeed < this->speed
            && this->maxSpeed < this->lastSpeed){

		    this->lastSpeed = this->speed;
			this->speed -= this->acceleration * dt;

		}
		else{
            this->speed = this->lastSpeed = this->maxSpeed;
		}
	}
}

//ajusta a posição do Player de acordo com o estado
void Player::UpdatePosition(float dt){
    UpdateSpeed(dt);
    checkPosition(this->box.x - Camera::pos.x);
    //Volta a velocidade para o padrão após colisão
    CheckCollisionToResetSpeed();

    Camera::MoveToFloor( GetLayer() );
    Camera::SetSpeed(GetSpeed());

    float diff = this->box.x - Camera::pos.x;
    switch(this->movementState){
        case RUNNING:
            this->box.x += this->speed*100*dt;
            if(IsInPosition()){
                Camera::pos.x = box.x - baseX;
            }else if(diff < GetBaseX()){
                Camera::MoveX(dt*100/2);
            }else if(diff > GetBaseX()){
                Camera::MoveX(dt*100*3/2);
            }
            break;
        case EATING:
            this->box.x += this->speed*(dt*100/3);
            Camera::MoveX(dt*100/3);
            break;
        case STOPPING:
            this->maxSpeed = 0;
            this->acceleration = 5.5;
            this->box.x += this->speed*(dt*100/3);
            break;
    }
    switch(this->inputState){
        case GOING_DOWN:
            this->box.y += this->speed*(dt * 150);
            break;
        case GOING_UP:
            this->box.y -= this->speed*(dt * 150);
            break;
    }
    AdjustGoingUpOrDown();
}

//ajusta a posição do player quando troca de andar
void Player::AdjustGoingUpOrDown(){

    if(this->inputState != NO_INPUT){

        if(this->layer == LAYER_TOP && abs(this->box.y - LAYER_TOP_HEIGHT) < 10){							//
            this->inputState = NO_INPUT;
            this->box.y = LAYER_TOP_HEIGHT - (this->subLayer - 3)*26;
        }

        if(this->layer == LAYER_MIDDLE && abs(this->box.y - LAYER_MIDDLE_HEIGHT) < 10){
            this->inputState = NO_INPUT;
            this->box.y = LAYER_MIDDLE_HEIGHT - (this->subLayer - 3)*26;
        }

        if(this->layer == LAYER_BOTTON && abs(this->box.y - LAYER_BOTTON_HEIGHT) < 10){
            this->inputState = NO_INPUT;
            this->box.y = LAYER_BOTTON_HEIGHT - (this->subLayer - 3)*26;
        }
    }
}

void Player::StopIndestructiblePowerup(){
    if(this->isIndestructible){
        this->powerUp = NONE;
        this->powerupMusic.Stop();
        this->ChangeSpriteSheet(RUNNING_SPRITE, RUNNING_FRAMES);
        this->isIndestructible = false;
    }
}

void Player::SetNewSpeedAndPowerup(PowerUp powerup, float newSpeed, float maxSpeed){
        this->itemTimer.Restart();
        this->SetMaxSpeed(maxSpeed);
        this->speed = newSpeed;
        this->powerUp = powerup;
}

void Player::checkPosition(float diff){
	if(diff > this->baseX - DELTA_ACCEPT &&
        this->baseX + DELTA_ACCEPT > diff ){
        this->isRightPosition = true;
    }else{
        this->isRightPosition = false;
    }
}

/***
        SETS/GETS/BOOLEANS
***/

void Player::SetMaxSpeed(float maxSpeed){
    this->maxSpeed = maxSpeed;
}

void Player::SetAcceleration(float acceleration){
	this->acceleration = acceleration;
}

void Player::TimeOver(){
    this->timeOver = true;
}

bool Player::IsPlayerAlive(){
    if(this->player != nullptr)
        return true;
    else
        return false;
}

float Player::GetSpeed(){
	return this->speed;
}

float Player::GetAcceleration(){
	return this->acceleration;
}

int Player::GetX(){
    return box.x;
}

int Player::GetBaseX(){
    if(powerUp == SKATE) return baseX + SKATING_BASEX_INC;
    else return baseX;
}

int Player::GetLayer(){
    return this->layer;
}

int Player::GetSublayer(){
    return this->subLayer;
}

Player& Player::GetInstance(){
    return *player;
}

bool Player::IsIndestructible(){
    return this->isIndestructible;
}

bool Player::isPlayerColliding(){
    return this->isColliding;
}

bool Player::IsInPosition(){
    return this->isRightPosition;
}

bool Player::Is(std::string type){
	return type == PLAYER_TYPE;
}

bool Player::IsSurprise(){
    return this->isSurprise;
}

SurpriseType Player::GetSurpriseType(){
    return this->surpriseType;
}

float Player::GetAddTime(){
    return this->addTime;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
