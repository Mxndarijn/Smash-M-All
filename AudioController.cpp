#include "AudioController.h"
#include <iostream>
#include <thread>

AudioController::AudioController(int* volume) : volume(volume)
{
    soundEngine = irrklang::createIrrKlangDevice();
    soundEngine->setSoundVolume(static_cast<float>(*volume) / 100);
    //irrklang::ISoundSource* MenuSound = soundEngine->addSoundSourceFromFile("sounds/mariotheme.mp3");
    //irrklang::ISound* sound = soundEngine->play2D(MenuSound, false, false, true);
}

AudioController::~AudioController()
{
	
}

void AudioController::run()
{
	std::thread t(&AudioController::playContinuous, this);
	t.detach();
}

void AudioController::playContinuous()
{
	irrklang::ISoundSource* intro = soundEngine->addSoundSourceFromFile("sounds/mariotheme-MENU.mp3");
	irrklang::ISound* introSound = soundEngine->play2D(intro, false, false, true);
	while(!introSound->isFinished()){}
	irrklang::ISoundSource* menu = soundEngine->addSoundSourceFromFile("sounds/mariotheme-INTRO.mp3");
	irrklang::ISound* menuSound = soundEngine->play2D(intro, false, false, true);
}

void AudioController::switchStream()
{
	
}


