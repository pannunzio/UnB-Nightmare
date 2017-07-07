#include "Pombo.h"

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

Pombo::Pombo(){
    this->sp = Sprite("img/pombo.png", 4, 0.09);
    this->layer = LAYER_TOP;
    this->subLayer = 0;
    this->isDead = false;
    this->speed = -3;

    this->fazendoCaca = false;
    this->box.Centralize(Camera::GetX() + 1000, LAYER_TOP_HEIGHT - 200, this->sp.GetWidth(), this->sp.GetHeight());


    OpenSound("audio/pombo.wav");
    this->spriteSound.Play(1);
}

Pombo::~Pombo(){
    this->spriteSound.Stop();
}

void Pombo::Update(float dt){
    this->sp.Update(dt);

	this->box.x += this->speed * dt * 100;

    if(!this->fazendoCaca && this->box.x - Camera::GetX() < 490){
        DEBUG_PRINT("FAZENDO CAQUINHA!!")
        this->FazCaca();
        this->fazendoCaca = true;
    }

    if(this->box.x - Camera::GetX() + this->sp.GetWidth() < 0)
		this->isDead = true;
}

void Pombo::Render(){
    this->sp.RenderFlipped(this->box.x - Camera::GetX(), this->box.y - Camera::GetY());
}

void Pombo::NotifyCollision(GameObject* other){
    //pombo não collide com nada
}

bool Pombo::Is(std::string type){
    return (type == "Pombo");
}

int Pombo::GetLayer(){
    return this->layer;
}

int Pombo::GetSublayer(){
    return this->subLayer;
}

void Pombo::FazCaca(){
    Vec2 shootPos = box.CenterPos();
//    CacaDePombo* caquinha = new CacaDePombo(shootPos.x, shootPos.y, "img/cacaPombo.png", 3, 1, true, box.x, box.y, speed);
    CacaDePombo* caquinha = new CacaDePombo(shootPos.x, shootPos.y);
//    caquinha->SetSubLayer(rand()%3+1);//Player::GetInstance().GetSublayer());
    Game::GetInstance().GetCurrentState().AddObject(caquinha);
}


#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
