/*
 * Clock.cpp
 *
 *  Created on: 21 de mai de 2016
 *      Author: Caio
 */

#include "Clock.h"

void Clock::Update(float dt){
	timer.Update(dt);
	seconds = timer.Get();
	if(timer.Get() > 60){
		minutes++;
		seconds = 0;
		timer.Restart();
	}
}
