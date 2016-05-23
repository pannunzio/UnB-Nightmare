#include "Clock.h"
#include "Resources.h"

//TIRAR ESSA CONSTANTE DAQUI
#define CONSTANTE 5

Clock::Clock(): doisPontos("font/Sketch College.ttf", 40, BLENDED, " : ", TEXT_WHITE, 980, 17){
    //VALOR ARBITRARIO COLOCAR NO DEFINES DEPOIS
    this->time = 60;
}

void Clock::Update(float dt){
	this->time -= dt;
}

void Clock::Render(){
    Text* sec1 = Resources::GetNumber(GetSeconds1());
    Text* sec2 = Resources::GetNumber(GetSeconds2());
    Text* minutes = Resources::GetNumber(GetMinutes());
    sec1->Render(0,0);
    sec2->Render(25,0);
    this->doisPontos.Render(50, 0);
    minutes->Render(75,0);
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
