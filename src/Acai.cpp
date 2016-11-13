#include "Acai.h"

Acai::Acai(int layer, int subLayer){
    this->sp = Sprite(ACAI_SPRITE, ACAI_FRAMES, ACAI_FTIME);
    this->captureSound.Open(ACAI_AUDIO, SOUND_CHANNEL_5);
    SetAssets(layer, subLayer);
}

bool Acai::Is(string type){
    return type == ACAI_TYPE;
}
