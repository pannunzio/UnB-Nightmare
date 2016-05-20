/*
 * Timer.h
 *
 *  Created on: 5 de mai de 2016
 *      Author: Caio
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer {
public:
	Timer();
	void Update(float dt);
	void Restart();
	float Get();
private:
	float time;
};

#endif /* TIMER_H_ */
