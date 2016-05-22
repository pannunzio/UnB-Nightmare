#ifndef CLOCK_H_
#define CLOCK_H_

#include "Text.h"

class Clock {
public:
    Clock();

	void Update(float dt);
    void Render();

	float GetTime();
	int GetMinutes();
	int GetSeconds1();
	int GetSeconds2();
private:
	float time;
	Text doisPontos;
};

#endif /* CLOCK_H_ */
