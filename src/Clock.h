#ifndef CLOCK_H_
#define CLOCK_H_

#include <sstream>

#include "Defines.h"
#include "Text.h"
#include "Resources.h"
#include <string>

using std::string;

class Clock {
public:
    Clock();

	void Update(float dt);
    void Render();

	float GetTime();
	void SetTime(float);
	int GetMinutes();
	int GetSeconds1();
	int GetSeconds2();
	void StopClock();
	void StartClock();

	string GetText();

	int GetSecondsTotal();

    //adiciona e subtrai um tempo constante do tempo.
    //multiplica pelo peso do objeto
	void AddTimeToTime(int peso);
	void SubtractTimeFromTime(int peso);

private:
	float time;
	string text;
	bool running;
};

#endif /* CLOCK_H_ */
