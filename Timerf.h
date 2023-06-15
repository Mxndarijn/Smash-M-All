#pragma once

class Timerf 
{
	int delay;
	bool& check;
public:
	Timerf(int delay, bool& check);
	~Timerf();

	void startTimer();

private:
	void run();
};