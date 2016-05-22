#include "Clock.h"
#include "Resources.h"

Clock::Clock(): doisPontos("font/arial.ttf", 34, SOLID, " : ", TEXT_BLACK, 980, 15){
    //VALOR ARBITRARIO COLOCAR NO DEFINES DEPOIS
    this->time = 62;
}

void Clock::Update(float dt){
	this->time -= dt;
}

void Clock::Render(){
    Text* sec1 = Resources::GetNumber(GetSeconds1());
    Text* sec2 = Resources::GetNumber(GetSeconds2());
    Text* minutes = Resources::GetNumber(GetMinutes());
    sec1->Render(0,0);
    sec2->Render(20,0);
    this->doisPontos.Render(40, 0);
    minutes->Render(50,0);
}

float Clock::GetTime(){
    return this->time;
}

int Clock::GetMinutes(){
    return (int)this->time/60;
}

//casa mais aa direita
int Clock::GetSeconds1(){
    int numero = (int) this->time%60;
    numero = numero % 10;
    return numero;
}

//casa mais aa esquerda
int Clock::GetSeconds2(){
    int numero = (int) this->time%60;
    numero = (int)numero / 10;
    return numero;
}
