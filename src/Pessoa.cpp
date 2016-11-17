#include "Pessoa.h"

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

Pessoa::Pessoa(): Obstacle(){
    DEBUG_PRINT("Pessoa::Pessoa()-begin-")
    GetSprite();

	this->spriteSound = Sound(4);
	this->GetXingamentoSound();
    DEBUG_PRINT("Pessoa::Pessoa()-end-")
}

Pessoa::~Pessoa(){
    spriteSound.Stop();
}

void Pessoa::Render(){
    if(this->isParada){
        this->sp.Render(this->box.x - Camera::GetX(), this->box.y - Camera::GetY() - 20);
    } else {
        if(this->speed >= 0)
    	 	this->sp.Render(this->box.x - Camera::GetX(), this->box.y - Camera::GetY() - 30);
		else
			this->sp.RenderFlipped(this->box.x - Camera::GetX(), this->box.y - Camera::GetY() - 30);
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
        case 1:
            fileName = "audio/Oxe2.wav";
            break;
        case 2:
            fileName = "audio/Odoida3.wav";
            break;
        case 3:
            fileName = "audio/Oxe1.wav";
            break;
        case 4:
            fileName = "audio/Odoida2.wav";
            break;
        case 5:
            fileName = "audio/Odoida3.wav";
            break;
        case 6:
            fileName = "audio/Ai6.wav";
            break;
        case 7:
            fileName = "audio/Ai5.wav";
            break;
        case 8:
            fileName = "audio/Uh2.wav";
            break;
        case 9:
            fileName = "audio/Ai3.wav";
            break;
        case 10:
            fileName = "audio/Ai2.wav";
            break;
        case 11:
            fileName = "audio/Ai1.wav";
            break;
    }
    OpenSound(fileName);
}

void Pessoa::GetSprite(){
    if(rand()%2 > 0){
        this->speed = 0;
        this->isParada = true;
        switch(rand()%2 + 1){
            case 1:
                this->sp = Sprite("img/parado1.png", 1, 1);
                break;
            case 2:
                this->sp = Sprite("img/parada.png", 6, 0.2);
                break;
            default:
                break;
        }
    }else{
        int aux = rand()%2; //0 ou 1
        switch(aux){
            case MENINA:
                this->sp = Sprite(MENINA_FILE, MENINA_FRAMES, MENINA_FTIME);
                break;
            case MENINO:
                this->box.y -= 10; //gambiarra!
                this->sp = Sprite(MENINO_FILE, MENINO_FRAMES, MENINO_FTIME);
                break;
            default:
                break;
        }
    }
    this->box.w = sp.GetWidth();
    this->box.h = sp.GetHeight();
}


#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
