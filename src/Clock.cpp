#include "Clock.h"
#include "Resources.h"
#include <sstream>

//TIRAR ESSA CONSTANTE DAQUI
#define CONSTANTE 5

//lembrar de mudar o starting value da text
Clock::Clock(): text("font/ComicNeue_Bold.otf", 40, BLENDED, "0 : 50", TEXT_WHITE, 980, 17){
    running = true;
}

void Clock::SetTime(float time){
    this->time = time;
}

void Clock::Update(float dt){
    if(running){
        this->time -= dt;

        std::stringstream novoTempo;
        novoTempo << GetMinutes() << " : " << GetSeconds2() << GetSeconds1();

        this->text.SetText(novoTempo.str());
    }
}

void Clock::Render(){
    this->text.Render(75,0);
}

float Clock::GetTime(){
    return this->time;
}

int Clock::GetMinutes(){
    return (int)this->time/60;
}

//casa mais aa direita
int Clock::GetSeconds1(){
    return GetSecondsTotal()%10;
}

//casa mais aa esquerda
int Clock::GetSeconds2(){
    return GetSecondsTotal()/10;
}

int Clock::GetSecondsTotal(){
    return (int) this->time%60;
}

void Clock::AddTimeToTime(int peso){
    this->time += CONSTANTE*peso;
}

void Clock::SubtractTimeFromTime(int peso){
    this->time -= CONSTANTE*peso;
}

void Clock::StopClock(){
    this->running = false;
}

void Clock::StartClock(){
    this->running = true;
}
