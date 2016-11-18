#include "Manifestacao.h"

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

Manifestacao::Manifestacao():Obstacle(){
    DEBUG_PRINT("Manifestacao::Manifestacao()-begin-")
    this->sp = Sprite(MANIFESTACAO_SPRITE, MANIFESTACAO_FRAMES, MANIFESTACAO_FTIME);
	this->isCollidingWithPlayer = false;

    this->speed = 2 + rand()%10/10;

	this->layer = LAYER_MIDDLE;
	this->subLayer = SUBLAYER_BOTTON;
	this->box.w = sp.GetWidth();
	this->box.h = sp.GetHeight();
	this->box.x = Player::GetInstance().GetX() + DEFAULT_OBSTACLE_DISTANCE + SUBLAYER_HEIGHT;
	SetHeight();


    spriteSound.Open(MANIFESTACAO_SOUND, 2);

    if(!spriteSound.IsPlaying(2))
        spriteSound.Play(-1);
    else {
        if(!spriteSound.IsPlaying(7)){
            spriteSound.SetChannel(7);
            spriteSound.Play(-1);
        }
        else if(!spriteSound.IsPlaying(8)){
            spriteSound.SetChannel(8);
            spriteSound.Play(-1);
        }
    }
    DEBUG_PRINT("Manifestacao::Manifestacao()-end-")
}

Manifestacao::~Manifestacao(){
    DEBUG_PRINT("destroy manifestacao")
    spriteSound.Stop(1);
}

void Manifestacao::Render(){
    this->sp.Render(this->box.x - Camera::GetX(), this->box.y - Camera::GetY());
}

void Manifestacao::NotifyCollision(GameObject* other){
//    if(!other->Is("Player")){
//        this->isCollidingWithPlayer = false;
//    }
//    else{
//        DEBUG_PRINT("Manifestacao colidindo com Player")
//        this->isCollidingWithPlayer = true;
//    }
    //manifestacao nao faz nada, fica la de boa na dela ,manifestando e atrapalhando o coredor
}

bool Manifestacao::Is(std::string type){
    return type == "Manifestacao";
}

int Manifestacao::GetLayer(){
    return this->layer;
}

int Manifestacao::GetSublayer(){
    if(Player::player != nullptr)
        return Player::GetInstance().GetSublayer();
    else
        return SUBLAYER_BOTTON;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
