#include "Timerf.h"
#include <iostream>

Timerf::Timerf(int delay, bool& check) : delay(delay), check(check)
{

}

Timerf::~Timerf() 
{
}

void Timerf::startTimer() 
{
	started = true;
	timeThread = std::thread(&Timerf::run, this);
	timeThread.detach();
}

void Timerf::run() 
{
	while (started) {
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		std::cout << "Done with threading" << std::endl;
		check = true;
	}
	
	// Clean up the thread if it is joinable
	if (timeThread.joinable())
	{
		timeThread.join();
	}
}