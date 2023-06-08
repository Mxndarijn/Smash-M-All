#pragma once
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

class AudioController
{
public:
	AudioController(int* volume);
	~AudioController();
	irrklang::ISoundEngine* soundEngine;
	int* volume;
	void run();
	void switchStream();
private:
	void playContinuous();
};