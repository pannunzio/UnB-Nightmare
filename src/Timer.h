#ifndef TIMER_H_
#define TIMER_H_

class Timer {
public:
	Timer();
	void Update(float dt);
	void Restart();
	float GetCurrentTime();
	void SetTimer(float time);
	bool isFinished();

private:
	float currentTime;
	float timer;
};

#endif
