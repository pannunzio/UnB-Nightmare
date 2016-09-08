#include "Obstacle.h"
#include "Manifestacao.h"
#include "Player.h"
#include "Camera.h"

Manifestacao::Manifestacao(){
    cout << "NEW MANIFEST!! " << endl;
    this->sp = Sprite("img/manifest.png", 6, 0.2);
//    this->sp = Sprite("img/manifest-block.png", 1, 1);
	this->speed = 2;
	if(this->speed != 0)
		this->speed += rand()%10/10;

	this->canBlock = true;
	this->isDead = false;

	this->layer = LAYER_MIDDLE;
	this->subLayer = SUBLAYER_BOTTON;

	this->spriteSound = Sound(-1);


	// ou seja, vai dar respawn se passar no teste
	this->box.x = Player::player->box.x + 1200;


    this->box.y = ITEM_HEIGHT_L2 + 30;

    // tem q ser tipo assim os outros tbm, dps alguem arruma ai
//    this->box.y += this->sp.GetHeight();
    this->box.y -= (this->subLayer - 3) * 26;

    // consertar isso para pegar geral

    spriteSound.Open("audio/manifestacao_11s.wav");
//    	spriteSound.PlayArbitraryFadeIn(1, 2);
    spriteSound.Play(1);
}

Manifestacao::~Manifestacao(){

}

void Manifestacao::Update(float dt){
	this->sp.Update(dt);
//	cout << "manifest update" << endl;
	this->box.x += this->speed * dt * 100;

    if(this->box.x - Camera::pos.x + this->sp.GetWidth()< 0){
		this->isDead = true;
        this->spriteSound.Stop();
    }
}

void Manifestacao::Render(){
    cout<< "manifest render" << endl;
    this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 120);
}

void Manifestacao::NotifyCollision(GameObject* other){
    if(other->Is("Player"))
        cout << "Collision!" << endl;
    //manifestacao nao faz nada, fica la de boa na dela ,manifestando e atrapalhando o coredor
}

bool Manifestacao::Is(std::string type){
    return type == "Manifestacao";
}

int Manifestacao::GetLayer(){
    return this->layer;
}

int Manifestacao::GetSublayer(){
    return Player::player->GetSublayer();
}
