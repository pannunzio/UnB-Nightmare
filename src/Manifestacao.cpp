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

Manifestacao::Manifestacao(){
    DEBUG_PRINT("CREATE NEW MANIFESTACAO")
    this->sp = Sprite("img/manifest.png", 6, 0.2);
	this->speed = 2 + rand()%10/10;
	this->canBlock = true;
	this->isDead = false;
	this->layer = LAYER_MIDDLE;
	this->subLayer = SUBLAYER_BOTTON;
	this->spriteSound = Sound(-1);
	this->isCollidingWithPlayer = false;

	this->box.x = Player::GetInstance().GetX() + 1200;

    this->box.y = LAYER_MIDDLE_HEIGHT + 30;
    this->box.y -= (this->subLayer - 3) * 26;

    spriteSound.Open("audio/manifestacao_11s.wav", 2);

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
}

Manifestacao::~Manifestacao(){
    DEBUG_PRINT("destroy manifestacao")
    spriteSound.Stop(1);
}

void Manifestacao::Render(){
    this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 120);
}

void Manifestacao::NotifyCollision(GameObject* other){
    if(!other->Is("Player"))
        this->isCollidingWithPlayer = false;
    else
        this->isCollidingWithPlayer = true;
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
