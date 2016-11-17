#include "Obstacle.h"

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

Obstacle::Obstacle(){

    DEBUG_PRINT("Obstacle::Obstacle()-begin-")
    this->canBlock = true;
    this->isDead = false;
	this->layer = Player::GetInstance().GetLayer(); //rand()%3 + 1;
	this->subLayer = Player::GetInstance().GetSublayer(); //rand()%3 + 1;
	this->speed = (rand()%3 + 1);

    this->box.x = Player::GetInstance().GetX() + DEFAULT_OBSTACLE_DISTANCE;
    if(this->layer == LAYER_TOP)
        this->box.y = LAYER_TOP_HEIGHT;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = LAYER_MIDDLE_HEIGHT;

    if(this->layer == LAYER_BOTTON)
        this->box.y = LAYER_BOTTON_HEIGHT;

    this->isSoundPlaying = false;
    this->spriteSound = Sound(-1);


    DEBUG_PRINT(" - Obstacle: " << this->box.x)
    DEBUG_PRINT(" - Obstacle: " << this->box.y)
    DEBUG_PRINT(" - Obstacle: " << this->layer)
    DEBUG_PRINT(" - Obstacle: " << this->subLayer)
    DEBUG_PRINT("Obstacle::Obstacle()-end-")
}

void Obstacle::Update(float dt){
	this->sp.Update(dt);
	this->box.x += this->speed * dt * 100;

    if(this->box.x - Camera::GetX() + this->sp.GetWidth()< 0){
		this->isDead = true;
        this->spriteSound.Stop();
    }
}

bool Obstacle::IsDead(){
    return this->isDead;
}

void Obstacle::OpenSound(string fileName){
    this->spriteSound.Open(fileName, 4);
}

void Obstacle::ChangeSpritesheet(string fileName, int frameCount, float frameTime){
    this->sp.Open(fileName);
    this->sp.SetFrameCount(frameCount);
    this->sp.SetFrameTime(frameTime);
    this->sp.SetClip(this->box.x, this->box.y, this->sp.GetWidth(), this->sp.GetHeight());
}

int Obstacle::GetSpeed(){
    return this->speed;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
