/*
 * Clock.h
 *
 *  Created on: 21 de mai de 2016
 *      Author: Caio
 */

#ifndef CLOCK_H_
#define CLOCK_H_


#include "Timer.h"
class Clock {
public:
	int minutes =0;
	int seconds = 0;
	void Update(float dt);
private:
	Timer timer;
};

#endif /* CLOCK_H_ */
