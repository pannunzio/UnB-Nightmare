#include "SurpriseItem.h"

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

SurpriseItem::SurpriseItem(int layer, int subLayer){
    this->sp = Sprite("img/surprise.png", 5, 0.09);
    this->captureSound.Open("audio/comida_getitem.wav", 5);
    SetAssets(layer, subLayer);
    SetHeight();

    int randSurprise = rand()%4 + 1;
    randSurprise = randSurprise%2;
    switch(randSurprise){
    case 1:{
        this->surprise = MANIFESTACAO;
        DEBUG_PRINT("surprise type is: MANIFESTACAO")
        break;
    }
    case 2:
    default:{
        this->surprise = PELADAO;
        DEBUG_PRINT("surprise type is: PELADAO")
        break;
    }
    }
}

bool SurpriseItem::Is(string type){
    return type == "Surprise!";
}

int SurpriseItem::GetSublayer(){
    if (!Player::GetInstance().IsDead()){
        return Player::GetInstance().GetSublayer();
    } else {
        return subLayer;
    }
}

SurpriseType SurpriseItem::GetSurprise(){
    return this->surprise;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
