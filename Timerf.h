#pragma once
#include <thread>

class Timerf 
{
	int delay;
	bool& check;
public:
	bool started = false;
	Timerf(int delay, bool& check);
	~Timerf();

	void startTimer();
	void stopTimer();
	void changeDelay(int newDelay);

private:
	void run();
	std::thread timeThread;
};