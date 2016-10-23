#include "SurpriseItem.h"

SurpriseItem::SurpriseItem(int layer, int subLayer){
    this->sp = Sprite("img/surprise.png", 5, 0.09);
    this->captureSound.Open("audio/comida_getitem.wav", 5);
    SetAssets(layer, subLayer);

    int randSurprise = rand()%4 + 1;
    randSurprise = randSurprise%2;
    switch(randSurprise){
    case 1:{
        this->surprise = MANIFESTACAO;
        cout << "surprise type is: MANIFESTACAO" << endl;
        break;
    }
    case 2:
    default:{
        this->surprise = PELADAO;
        cout << "surprise type is: PELADAO" << endl;
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
