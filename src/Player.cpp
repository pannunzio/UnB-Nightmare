#include "Player.h"

Player* Player::player = nullptr;
int Player::coffee_ammo = 0;

/***
        CONSTRUTOR
***/
Player::Player(float x, float y) : sp(RUNNING_FILE, RUNNING_FRAMES, RUNNING_FTIME){
	//Inicialização da referencia a Player
	this->player = this;

	//Inicialização de posição
	this->baseX = (int)x;
	this->subLayer = SUBLAYER_MIDDLE;
	this->layer = LAYER_MIDDLE;
	this->box.Centralize(x,y,sp.GetWidth(),sp.GetHeight());
	this->isRightPosition = true;
    this->layer = rand()%3 +1;

	//inicialização de estado
	this->movementState = RUNNING;
    this->targetSpeed = speed = RUNNING_SPEED;
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

    //Coisas que não fazem muito sentido estar aqui
	this->hud = Text(TEXT_FONT_FILE, 28, SOLID, TEXT_INIT, TEXT_WHITE, 40,50);
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
    if(timeOver == true) PlayerStops();
    MoveGirl(); // faz os movimentos do input
    UpdatePowerUp(dt);

    //colocando na posicao certa o player
    checkPosition(this->box.x - Camera::pos.x);
    //Volta a velocidade para o padrão após colisão
    CheckCollisionToResetSpeed();
    AdjustSpeed(dt);
    SetPositionToMovementState(dt);

    AdjustGoingUpOrDown();

    this->isColliding = false;
    this->isPassingMapObject = false;
}

void Player::PlayerStops(){
    switch(movementState){
        case RUNNING:
            this->ChangeSpriteSheet(STOPPING_FILE, STOPPING_FRAMES, STOPPING_TIMES);
            movementState = STOPPING;
            break;
        default:
            break;
    }
    playerControl = false;
}

void Player::Render(){
	this->sp.Render((int)(this->box.x - Camera::pos.x), (int)(this->box.y - Camera::pos.y));
	this->RenderHud();
	this->SetSpriteScale();
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
        if(!isIndestructible){
            this->isColliding = true;
            this->wasColliding = true;
            this->SetTargetSpeed(0.0);
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
        StopIndestructiblePowerup();

        this->isColliding = true;
        this->wasColliding = true;
        this->speed = 2;

        // se ficar apertando vai mais rapido
        if(InputManager::GetInstance().KeyPress(SDLK_d))
        	this->box.x += 20;
    }

    if(other->Is("COFFEE")){
        this->coffee_ammo++;
    }

    if(other->Is("SKATE")){
        if(!this->isPlayingMusic && this->powerUp != SKATE){
            this->powerupMusic.Open(SKATING_MUS, 5);
            this->powerupMusic.Play(1);
            this->powerupMusic.SetVolume(180);
        }

        SetNewSpeedAndPowerup(PowerUp::SKATE, this->speed, SKATING_SPEED);
        this->ChangeSpriteSheet(SKATING_FILE, SKATING_FRAMES);
    }

    if(other->Is("GGLIKO")){//DEBUG aperte G para ficar no estado EATING
        StopIndestructiblePowerup();
        SetNewSpeedAndPowerup(PowerUp::COMIDA, 3.5, RUNNING_SLOW_SPEED);
        ChangeSpriteSheet(EATING_FILE, EATING_FRAMES);
        movementState = EATING;
    }

    //caca de pombo
    if(other->Is("Caca")){
        cout << "opa, caca!" << endl;
        StopIndestructiblePowerup();
        SetNewSpeedAndPowerup(PowerUp::CACA_DE_POMBO, 3.5, RUNNING_SLOW_SPEED);
    }

    if(other->Is("Escada")){
        this->isPassingMapObject = true;
    }

    if(other->Is("Agua")){
        StopIndestructiblePowerup();
        SetNewSpeedAndPowerup(PowerUp::NONE, 3.0, RUNNING_SLOW_SPEED);
    }
}

bool Player::IsTargetSpeed(float targetSpeed){
	if(targetSpeed < 0) // se algo a levar para tras
		this->speed = targetSpeed;
	if(abs(this->speed - targetSpeed) <= 0.005)
		return true;
	return false;
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

void Player::RenderHud(){
    std::stringstream hudString;
    hudString << "Coffee: " << coffee_ammo;
    this->hud.SetText(hudString.str());
	this->hud.Render(0, 0);

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
        this->box.y = ITEM_HEIGHT_L3 + 2;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = ITEM_HEIGHT_L2;

    if(this->layer == LAYER_BOTTON)
        this->box.y = ITEM_HEIGHT_L1;

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
    case SKATE:
        this->itemTimer.Update(dt);
        this->isPassingMapObject = false;
        this->isIndestructible = true;
        if (this->itemTimer.GetCurrentTime() > SKATING_TIME){
            EndPowerUp();
            this->ChangeSpriteSheet(RUNNING_FILE, RUNNING_FRAMES);
            this->movementState = RUNNING;
        }
        break;
    case COMIDA:
        this->itemTimer.Update(dt);
        if (this->itemTimer.GetCurrentTime() > EATING_TIME){
            EndPowerUp();
            this->ChangeSpriteSheet(RUNNING_FILE, RUNNING_FRAMES);
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
    this->SetTargetSpeed(RUNNING_SPEED);

    if(this->powerupMusic.IsPlaying())
        this->powerupMusic.Stop();

    if(this->IsIndestructible())
        this->isIndestructible = false;
}

void Player::CheckCollisionToResetSpeed(){
    if(!this->isColliding){
        if(this->wasColliding){
            this->speed = RUNNING_SPEED;
            this->SetTargetSpeed(RUNNING_SPEED);
            this->wasColliding = false;
        }
    }
}

void Player::AdjustSpeed(float dt){
	//ir acelerando at� a velocidade
	if(!this->IsTargetSpeed(targetSpeed)){
		if(this->targetSpeed > this->speed)
			this->speed += this->acceleration * dt;

		if(this->targetSpeed < this->speed)
			this->speed -= this->acceleration * dt;

		if(this->targetSpeed == 0){
			this->speed = 0;
		}
	}
}

//ajusta a posição do Player de acordo com o tipo do movimento
//(se ele se desloca de um lado para o outro ou de cima para baixo)
void Player::SetPositionToMovementState(float dt){

    //correndo
    SetPositionIncrement(dt);
    switch(this->movementState){
        case RUNNING:
            this->box.x += this->speed*GetPositionIncrement();
            break;
        case EATING:
            this->box.x += this->speed*GetPositionIncrement()/3;
            break;
    }
    switch(this->inputState){
        case GOING_DOWN:
            this->box.y += this->speed * dt * 150;
            break;
        case GOING_UP:
            this->box.y -= this->speed * dt * 150;
            break;
    }
}

//ajusta a posição do player quando troca de andar
void Player::AdjustGoingUpOrDown(){

    if(this->inputState != NO_INPUT){

        if(this->layer == LAYER_TOP && abs(this->box.y - ITEM_HEIGHT_L3) < 10){							//
            this->inputState = NO_INPUT;
            this->box.y = ITEM_HEIGHT_L3 - (this->subLayer - 3)*26;
        }

        if(this->layer == LAYER_MIDDLE && abs(this->box.y - ITEM_HEIGHT_L2) < 10){
            this->inputState = NO_INPUT;
            this->box.y = ITEM_HEIGHT_L2 - (this->subLayer - 3)*26;
        }

        if(this->layer == LAYER_BOTTON && abs(this->box.y - ITEM_HEIGHT_L1) < 10){
            this->inputState = NO_INPUT;
            this->box.y = ITEM_HEIGHT_L1 - (this->subLayer - 3)*26;
        }
    }
}

void Player::StopIndestructiblePowerup(){
    if(this->isIndestructible){
        this->powerUp = NONE;
        this->powerupMusic.Stop();
        this->ChangeSpriteSheet(RUNNING_FILE, RUNNING_FRAMES);
        this->isIndestructible = false;
    }
}

void Player::SetNewSpeedAndPowerup(PowerUp powerup, float newSpeed, float targetSpeed){
        this->itemTimer.Restart();
        this->SetTargetSpeed(targetSpeed);
        this->speed = newSpeed;
        this->powerUp = powerup;
}

void Player::checkPosition(float diff){
	if(diff > baseX - DELTA_ACCEPT &&
        baseX + DELTA_ACCEPT > diff ){
        //cout << "posicao certa!: " << box.x << endl;
        this->isRightPosition = true;
    }else{
        this->isRightPosition = false;
    }

}

/***
        SETS/GETS/BOOLEANS
***/

void Player::SetTargetSpeed(float targetSpeed){
    this->targetSpeed = targetSpeed;
}

void Player::SetAcceleration(float acceleration){
	this->acceleration = acceleration;
}

void Player::SetPositionIncrement(float dt){
    positionIncrement = 100 * dt;
}

void Player::TimeOver(){
    this->timeOver = true;
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
    if(powerUp == SKATE) return baseX + 100;
    else return baseX;
}

float Player::GetPositionIncrement(){
    return positionIncrement;
}

int Player::GetLayer(){
    return this->layer;
}

int Player::GetSublayer(){
    return this->subLayer;
}

bool Player::IsRightPosition(){
	return this->isRightPosition;
}

bool Player::IsIndestructible(){
    return this->isIndestructible;
}

bool Player::isPlayerColliding(){
    if(isColliding) return true;
    else return false;
}

bool Player::isInPosition(){
    if(isRightPosition) return true;
    else return false;
}

bool Player::Is(std::string type){
	return (type == "Player");
}
