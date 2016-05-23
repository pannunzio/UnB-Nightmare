#ifndef CLOCK_H_
#define CLOCK_H_

#include "Defines.h"
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

	int GetSecondsTotal();

    //adiciona e subtrai um tempo constante do tempo.
    //multiplica pelo peso do objeto
	void AddTimeToTime(int peso);
	void SubtractTimeFromTime(int peso);

private:
	float time;
	Text doisPontos;
};

#endif /* CLOCK_H_ */
