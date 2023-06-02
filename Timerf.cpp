#include "Timerf.h"
#include <iostream>
#include <thread>

Timerf::Timerf(int delay, bool *check) : delay(delay), check(check)
{

}

Timerf::~Timerf() {}

void Timerf::startTimer() 
{
	std::thread timeThread(&Timerf::run, this);
	timeThread.detach();
}

void Timerf::run() 
{
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	std::cout << "Done with threading" << std::endl;
	*check = true;
}