#include "Item.h"

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

Item::~Item(){
    this->captureSound.Stop();
}

void Item::Update(float dt){
    if(Player::player){
        this->sp.Update(dt);
    } else
        this->isDead = true;
}

void Item::Render(){
    this->sp.Render(this->box.x - Camera::GetX(), this->box.y - Camera::GetY());
}


bool Item::IsDead(){
    return this->isDead;
}

void Item::NotifyCollision(GameObject* other){
    if(other->Is("Player")){
        DEBUG_PRINT("BATI NO PLAYERRR SL: " << this->GetSublayer() << " SUB:: " << this->subLayer)
        this->isDead = true;
        this->captureSound.Play(1);
    }

    if(this->box.x < -100){
        this->isDead = true;
    }
}

int Item::GetLayer(){
    return this->layer;
}

int Item::GetSublayer(){
    return this->subLayer;
}

void Item::SetAssets(int layer, int subLayer){
    this->layer = layer;
    this->subLayer = subLayer;

    this->box.x = Player::GetInstance().GetX() + 1200;
    this->box.y = 0;
    this->box.w = this->sp.GetWidth();
    this->box.h = this->sp.GetHeight();

    this->isDead = false;

    this->captureSound.SetChannel(5);

	if(this->layer == LAYER_TOP)
        this->box.y = LAYER_TOP_HEIGHT;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = LAYER_MIDDLE_HEIGHT;

    if(this->layer == LAYER_BOTTON)
        this->box.y = LAYER_BOTTON_HEIGHT;

    if (this->subLayer < SUBLAYER_TOP)
        this->box.y += SUBLAYER_HEIGHT;

    if(this->subLayer == SUBLAYER_BOTTON)
        this->box.y += SUBLAYER_HEIGHT;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
