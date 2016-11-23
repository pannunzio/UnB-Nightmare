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
	this->playerAlive = true;
    this->sp = Sprite(RUNNING_SPRITE, RUNNING_FRAMES, RUNNING_FTIME);
    //Inicialização de posição
	this->baseX = (int)x;
	this->subLayer = SUBLAYER_MIDDLE;
	this->layer = LAYER_MIDDLE;
	this->box.w = this->sp.GetWidth();
	this->box.h = this->sp.GetHeight();
	this->box.x = x;
	this->box.y = y - this->box.h;//alinha pelo pé da imagem
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
    this->switchFloor = false;
    this->isSwitchingFloors = false;

    //Inicialização de conhecimentos externos
    this->timeOver = false;
    this->playerControl = true;//modificar para criar o inicio de jogo
    //Inicialização referente a colisão
    this->isColliding = false;
    this->isPassingMapObject = false;
    this->isSurprise = false;
    this->surpriseType = NO_SURPRISE;
    this->addTime = 0.0;

    //Inicialização do balão
    this->ballonRender = 0;

    DEBUG_PRINT(" - PlayerX: " << this->box.x)
    DEBUG_PRINT(" - PlayerY: " << this->box.y)
    DEBUG_PRINT(" - PlayerLayer: " << this->layer)
    DEBUG_PRINT(" - PlayerSubLay: "<< this->subLayer)

    DEBUG_PRINT("MagicButtons:")
    DEBUG_PRINT(" - Ganhar 10 segundos: 1")
    DEBUG_PRINT(" - Ir para Comendo:    2")
    DEBUG_PRINT(" - Ir para Skating:    2")
    DEBUG_PRINT(" - opacidade 100:      0")
    DEBUG_PRINT(" - FadeIn():           9")
    DEBUG_PRINT(" - FadeOut():          8")
    DEBUG_PRINT(" - FadeTo(30):         7")
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
	DEBUG_ONLY(MagicButtons())
	DEBUG_PRINT("Player::Update()-begin-")
	//atualiza o sprite
	this->sp.Update(dt);

	//se for o caso, atualiza o balão
    if(!this->isColliding)
        this->ballonRender = 0;

    if(timeOver == true)
        PlayerStops();

    MoveGirl();
    UpdatePowerUp(dt);
    UpdatePosition(dt);

    this->isColliding = false;
    this->isPassingMapObject = false;
    this->addTime = 0.0;
    this->isSwitchingFloors = false;
    DEBUG_PRINT("Player::Update()-end-")
}

void Player::Render(){
	this->sp.Render((int)(this->box.x - Camera::GetX()), (int)(this->box.y - Camera::GetY()));
}

bool Player::IsDead(){
    DEBUG_PRINT("Player::IsDead()-begin-")
    if(this->box.x + this->box.w - Camera::GetX() < 10 ){//if(Camera::GetX() + 10 > this->box.x + this->box.w){//if(this->box.x + this->box.w - Camera::GetX() > 10){
        this->playerAlive = false;
        this->playerControl = false;
	}
	DEBUG_PRINT("Player::IsDead()-end-")
	return false;
}

void Player::NotifyCollision(GameObject* other){
    if(!this->timeOver && !other->Is("Escada")){
        Obstacle* obst = (Obstacle*) other;
        this->SetMaxSpeed(obst->GetSpeed());
        this->speed = obst->GetSpeed();
    }
    if(other->Is("Pessoa") || other ->Is("Zumbi") || other->Is("Lixeira")){
        DEBUG_PRINT("colidiu Pessoa/Zumbi/Lixeira")
        DEBUG_PRINT("player(x + w): " << this->box.x + this->box.w)
        if(!isIndestructible){
            this->isColliding = true;
        } else {
            //se estiver com um powerup que dá indestrutibilidade, desvia dos obstaculos principais
            //está conflitando com os inputs e tirando o player do lugar
//            if (this->subLayer == 3){
//                this->subLayer--;
//            } else if (this->subLayer == 1){
//                this->subLayer++;
//            } else if (this->subLayer == 2){
//                this->subLayer++;
//            }
        }
    }else if(other->Is("Manifestacao")){
        DEBUG_PRINT("colidiu MANIFESTACAO")
        StopIndestructiblePowerup();
        this->isColliding = true;
        this->ballonRender = 1;
        if(InputManager::GetInstance().KeyPress(SDLK_d))
        	this->box.x += PLAYER_MANIFEST_INC;

    }else if(other->Is("NonColliding")){
        DEBUG_PRINT("nudez no campus!")
        this->isColliding = true;
        if(!this->timeOver)
            this->speed /= this->speed;
    }else if(other->Is("Cafe")){
        DEBUG_PRINT("colidiu CAFE")
        this->coffee_ammo++;
    }else if(other->Is("Skate")){
        DEBUG_PRINT("colidiu SKATE")
        if(!this->isPlayingMusic && this->powerUp != SKATE){
            this->powerupMusic.Open(SKATING_MUS, 5);
            this->powerupMusic.Play(1);
            this->powerupMusic.SetVolume(180);
        }
        SetNewSpeedAndPowerup(PowerUp::SKATE, this->speed, SKATING_SPEED);
        this->ChangeSpriteSheet(SKATING_SPRITE, SKATING_FRAMES);
    }else if(other->Is("Acai")){
        DEBUG_PRINT("colidiu ACAI")
        StopIndestructiblePowerup();
        SetNewSpeedAndPowerup(PowerUp::COMIDA, 3.5, RUNNING_SLOW_SPEED);
        ChangeSpriteSheet(EATING_FILE, EATING_FRAMES);
        movementState = EATING;
    }else if(other->Is("Caca")){
        DEBUG_PRINT("colidiu CACA")
        StopIndestructiblePowerup();
        SetNewSpeedAndPowerup(PowerUp::CACA_DE_POMBO, 3.5, RUNNING_SLOW_SPEED);
    }else if(other->Is("Escada")){
        DEBUG_PRINT("colidiu ESCADA")
        switch(this->layer){
            case LAYER_TOP:
                if(this->subLayer == SUBLAYER_BOTTON){
                    this->ballonRender = 2;
                    this->isPassingMapObject = true;
                }
                break;
            case LAYER_MIDDLE: case LAYER_BOTTON:
                if(this->subLayer == SUBLAYER_TOP){
                    this->ballonRender = 2;
                    this->isPassingMapObject = true;
                }
        }

    }else if(other->Is("Agua")){
        DEBUG_PRINT("colidiu AGUA")
        StopIndestructiblePowerup();
        SetNewSpeedAndPowerup(PowerUp::NONE, 3.0, RUNNING_SLOW_SPEED);
    }else if(other->Is("Surprise!")){
        DEBUG_PRINT("colidiu SURPRISE!")
        this->isSurprise = true;
        SurpriseItem* item = (SurpriseItem*) other;
        this->surpriseType = item->GetSurprise();
    }else if(other->Is("ClockItem")){
        DEBUG_PRINT("colidiu CLOCKITEM")
        ClockItem* item = (ClockItem*) other;
        this->addTime = item->GetTimeToAdd();
    }
}

void Player::MoveGirl(){
    if(playerControl == true){
        MoveSameFloor();
        MoveThroughFloors();
        if(this->isSwitchingFloors && !this->switchFloor)
            this->switchFloor = true;
        else if(!this->isSwitchingFloors || this->switchFloor)
            this->switchFloor = false;
    }
    SetSpriteScale();
}

void Player::MoveSameFloor(){
	if(InputManager::GetInstance().KeyPress(SDLK_w)){
		if(this->subLayer <= 2){
			this->subLayer++;
			this->box.y -= SUBLAYER_HEIGHT;
		}
    }else if(InputManager::GetInstance().KeyPress(SDLK_s)){
		if(this->subLayer >= 2){
			this->subLayer--;
			this->box.y += SUBLAYER_HEIGHT;
		}
	}else if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
        Shoot();
    }
}

//Confere se o player pode ou nao subir/descer escada
void Player::MoveThroughFloors(){
    if(this->powerUp != PowerUp::SKATE){
        #ifndef DEBUG
        if(this->layer == LAYER_TOP && this->subLayer == SUBLAYER_BOTTON ||
           this->layer == LAYER_MIDDLE && this->subLayer == SUBLAYER_TOP ||
           this->layer == LAYER_BOTTON && this->subLayer == SUBLAYER_TOP
           && this->isPassingMapObject){
        #endif // DEBUG
            switch(this->layer){
                case LAYER_MIDDLE:
                    if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
                        this->layer++;
                        this->subLayer = SUBLAYER_BOTTON;
                        this->inputState = GOING_UP;
                        this->box.y = LAYER_TOP_HEIGHT - box.h + SUBLAYER_HEIGHT;
                        this->isSwitchingFloors = true;
                    }else if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
                        this->layer--;
                        this->subLayer = SUBLAYER_TOP;
                        this->inputState = GOING_DOWN;
                        this->box.y = LAYER_BOTTON_HEIGHT - box.h - SUBLAYER_HEIGHT;
                        this->isSwitchingFloors = true;
                    }
                    break;
                case LAYER_BOTTON:
                    if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
                        this->layer++;
                        this->subLayer = SUBLAYER_TOP;
                        this->inputState = GOING_UP;
                        this->box.y = LAYER_MIDDLE_HEIGHT - box.h - SUBLAYER_HEIGHT;
                        this->isSwitchingFloors = true;
                    }
                    break;
                case LAYER_TOP:
                    if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
                        this->layer--;
                        this->subLayer = SUBLAYER_TOP;
                        this->inputState = GOING_DOWN;
                        this->box.y = LAYER_MIDDLE_HEIGHT - box.h - SUBLAYER_HEIGHT;
                    }
                    break;
                default:
                    this->isSwitchingFloors = false;
                    break;
            }
        #ifndef DEBUG
        }
        #endif // DEBUG
    }
}

void Player::PlayerStops(){
    //é possivel colocar um tipo de parada por estado do player
    switch(movementState){
        case RUNNING:
            this->ChangeSpriteSheet(STOPPING_SPRITE, STOPPING_FRAMES, STOPPING_TIMES);
            movementState = STOPPING;
            break;
        default:
//            this->ChangeSpriteSheet(STOPPING_SPRITE, STOPPING_FRAMES, STOPPING_TIMES);
//            movementState = STOPPING;
            break;
    }
    playerControl = false;
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

void Player::ChangeSpriteSheet(string file, int frameCount, int times){
    this->sp.Open(file);
    this->sp.SetFrameCount(frameCount);
    this->sp.SetAnimationTimes(times);
    this->sp.SetClip(this->box.x, this->box.y, this->sp.GetWidth(), this->sp.GetHeight());
}

void Player::SetSpriteScale(){
    if(this->subLayer == SUBLAYER_TOP)
    	this->sp.SetScale(SPRITE_RESIZE_TOP);
    if(this->subLayer == SUBLAYER_MIDDLE)
        this->sp.SetScale(SPRITE_RESIZE_MIDDLE);
    if(this->subLayer == SUBLAYER_BOTTON)
        this->sp.SetScale(SPRITE_RESIZE_BOTTON);
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

void Player::UpdateSpeed(float dt){
    if(!this->isColliding && !this->timeOver) this->speed = RUNNING_SPEED;
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
    DEBUG_PRINT("Player::UpdatePosition()-begin-")
    UpdateSpeed(dt);
    checkPosition(this->box.x - Camera::GetX());

    Camera::MoveToFloor( GetLayer() );

    float diff = this->box.x - Camera::GetX();
    switch(this->movementState){
        case RUNNING:
            this->box.x += this->speed*100*dt;
            if(this->isRightPosition){
                Camera::SetX(box.x - baseX);
            }else if(diff <= GetBaseX()){
                Camera::MoveX(dt*100*0.5);
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
        case SKATING:
            break;
    }
    DEBUG_PRINT("Player::UpdatePosition()-end-")
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
    if(this->isColliding == false){
        if(this->baseX + DELTA_ACCEPT > diff && diff > this->baseX - DELTA_ACCEPT){
            this->isRightPosition = true;
        }else{
            this->isRightPosition = false;
        }
    }else this->isRightPosition = false;
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
    return this->playerAlive;
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

int Player::GetY(){
    return box.y;
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

void Player::OffSurprise(){
    this->isSurprise = false;
    this->surpriseType = NO_SURPRISE;
}

float Player::GetAddTime(){
    return this->addTime;
}

bool Player::GetSwitchFloor(){
    return this->switchFloor;
}

/**
    DEBUG
**/
void Player::MagicButtons(){
    if(InputManager::GetInstance().KeyPress(SDLK_2)){
        this->movementState = EATING;
    }
    if(InputManager::GetInstance().KeyPress(SDLK_3)){
        this->movementState = SKATING;
    }
    if(InputManager::GetInstance().KeyPress(SDLK_0)){
        this->sp.SetAlpha(100);
    }
    if(InputManager::GetInstance().KeyPress(SDLK_9)){
        this->sp.FadeIn();
    }
    if(InputManager::GetInstance().KeyPress(SDLK_8)){
        this->sp.FadeOut();
    }
    if(InputManager::GetInstance().KeyPress(SDLK_7)){
        this->sp.FadeToValue(30);
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_6)){
        this->ballonRender = 2;
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
