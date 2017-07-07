#include "CacaDePombo.h"
#include "Animation.h"

CacaDePombo::CacaDePombo(float originX, float originY): sp(CACA_SPRITE, CACA_FRAMECOUNT, CACA_FRAMETIME),
                                                        colisaoPlayer("audio/caca_explosao.wav", 6){
    this->box.Centralize(originX, originY, this->sp.GetWidth(), this->sp.GetHeight());
	this->distanceLeft = 200;
	this->distanceLimit = 3;
    this->layer = LAYER_TOP;
    this->subLayer = Player::GetInstance().GetSublayer();
    this->gravidade = 5;
    this->speed.x = -300;
    this->speed.y = 0;
    this->isExplosion = false;
    this->animationOver = false;
}

CacaDePombo::~CacaDePombo(){
}

void CacaDePombo::Update(float dt){
    if(!this->isExplosion){
        this->speed.y += this->gravidade;
        this->distanceLeft --;
        this->box.x += this->speed.x * dt;
        this->box.y += this->speed.y * dt;
    } else {
        if(this->sp.IsAnimationFinished())
            this->animationOver = true;
    }
}

void CacaDePombo::Render(){
    this->sp.Render(this->box.x - Camera::GetX(), this->box.y - Camera::GetY());
}

bool CacaDePombo::IsDead(){
    if (this->distanceLeft <= distanceLimit && !this->isExplosion){
        if(this->colisaoPlayer.IsPlaying())
            this->colisaoPlayer.Stop(2);
        return true;
    }
    if(this->isExplosion && this->animationOver){
        return true;
    }
    return false;
}

void CacaDePombo::NotifyCollision(GameObject* other){
    if (other->Is("Player") && !this->isExplosion){
        this->distanceLeft = 0;
        this->colisaoPlayer.Play(1);
        this->isExplosion = true;
        this->sp.Open("img/cacaexplode.png");
        this->sp.SetFrameCount(6);
        this->sp.SetAnimationTimes(1);
        this->sp.SetClip(this->box.x, this->box.y, this->sp.GetWidth(), this->sp.GetHeight());
    }
}
bool CacaDePombo::Is(std::string type){
    if(!this->isExplosion)
        return (type == "Caca");
    else
        return (type == "Animation");
}

int CacaDePombo::GetLayer(){
    return this->layer;
}

int CacaDePombo::GetSublayer(){
    return Player::GetInstance().GetSublayer();
}
