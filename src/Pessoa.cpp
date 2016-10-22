#include "Pessoa.h"

Pessoa::Pessoa(){
    this->speed = (rand()%3 + 1);

    GetSprite();

	this->canBlock = true;
	this->isDead = false;
	this->layer = rand()%3 + 1;
	this->subLayer = rand()%3 + 1;

    this->isSoundPlaying = false;

	this->spriteSound = Sound(4);
	this->GetXingamentoSound();

	this->box.x = Player::GetInstance().GetX() + 1200;

    if(this->layer == LAYER_TOP)
        this->box.y = OBST_HEIGHT_L3 + 3;

    if(this->layer == LAYER_MIDDLE)
        this->box.y = OBST_HEIGHT_L2 + 10;

    if(this->layer == LAYER_BOTTON)
        this->box.y = OBST_HEIGHT_L1 + 5;

    this->box.y -= (this->subLayer - 3) * 25;
}

Pessoa::~Pessoa(){
    spriteSound.Stop();
}

void Pessoa::Render(){
    if(this->isParada){
        this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 20);
    } else {
        if(this->speed >= 0)
    	 	this->sp.Render(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 30);
		else
			this->sp.RenderFlipped(this->box.x - Camera::pos.x, this->box.y - Camera::pos.y - 30);
    }
}

void Pessoa::NotifyCollision(GameObject* other){
    if((other->Is("Coffee") || other->Is("Player")) && !this->isSoundPlaying){
        spriteSound.Play(1);
        this->isSoundPlaying = true;
    }

}

bool Pessoa::Is(string type){
    return type == "Pessoa";
}

int Pessoa::GetLayer(){
    return this->layer;
}

int Pessoa::GetSublayer(){
    return this->subLayer;
}

void Pessoa::GetXingamentoSound(){
    string fileName;

    switch(rand()%11 + 1){
    case 1:{
        fileName = "audio/Oxe2.wav";
        break;
    }
    case 2:{
        fileName = "audio/Odoida3.wav";
        break;
    }
    case 3:{
        fileName = "audio/Oxe1.wav";
        break;
    }
    case 4:{
        fileName = "audio/Odoida2.wav";
        break;
    }
    case 5:{
        fileName = "audio/Odoida3.wav";
        break;
    }
    case 6:{
        fileName = "audio/Ai6.wav";
        break;
    }
    case 7:{
        fileName = "audio/Ai5.wav";
        break;
    }case 8:{
        fileName = "audio/Uh2.wav";
        break;
    }case 9:{
        fileName = "audio/Ai3.wav";
        break;
    }
    case 10:{
        fileName = "audio/Ai2.wav";
        break;
    }
    case 11:{
        fileName = "audio/Ai1.wav";
        break;
    }
    }

    OpenSound(fileName);
}

void Pessoa::GetSprite(){
    if(rand()%2 + 1 > 1){

        this->speed = 0;
        this->isParada = true;
        switch(rand()%2 + 1){
        case 1:{
            this->sp = Sprite("img/parado1.png", 1, 1);
            return;
        }
        case 2:{
            this->sp = Sprite("img/parada.png", 6, 0.2);
            return;
        }
        default:
            return;
        }
    } else {
        int aux = rand()%2; //0 ou 1
        switch(aux){
        case MENINA:{
            this->sp = Sprite(MENINA_FILE, MENINA_FRAMES, MENINA_FTIME);
            return;
        }
        case MENINO:{
            this->sp = Sprite(MENINO_FILE, MENINO_FRAMES, MENINO_FTIME);
            return;
        }
        default:
            return;
        }
    }
}
