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

private:
	void run();
	std::thread timeThread;
};