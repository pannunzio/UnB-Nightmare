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

#endif
