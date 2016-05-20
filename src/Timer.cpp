/*
 * Timer.cpp
 *
 *  Created on: 5 de mai de 2016
 *      Author: Caio
 */

#include "Timer.h"


Timer::Timer(){
	time = 0;
}
void Timer::Update(float dt){
	time+= dt;
}
void Timer::Restart(){
	time = 0;
}
float Timer::Get(){
	return time;
}
