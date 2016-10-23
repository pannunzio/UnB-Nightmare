#include "Clock.h"

//lembrar de mudar o starting value da text
Clock::Clock(){
    running = true;
}

void Clock::SetTime(float time){
    this->time = time;
}

void Clock::Update(float dt){
    if(running){
        this->time -= dt;

        std::stringstream novoTempo;
        novoTempo << GetMinutes() << ":" << GetSeconds2() << GetSeconds1();

        this->text = novoTempo.str();
    }
}

void Clock::Render(){
}

string Clock::GetText(){
    return this->text;
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
    this->time += peso;
//    if(this->time < 0)
//        this->time = 0;
}

void Clock::SubtractTimeFromTime(int peso){
    this->time -= peso;
}

void Clock::StopClock(){
    this->running = false;
}

void Clock::StartClock(){
    this->running = true;
}
