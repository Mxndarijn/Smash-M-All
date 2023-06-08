#include "AudioController.h"

AudioController::AudioController(int* volume) : volume(volume)
{
    soundEngine = irrklang::createIrrKlangDevice();
    soundEngine->setSoundVolume(static_cast<float>(*volume) / 100);
    irrklang::ISoundSource* soundSource = soundEngine->addSoundSourceFromFile("sounds/mariotheme.mp3");
    irrklang::ISound* sound = soundEngine->play2D(soundSource, false, false, true);
}

AudioController::~AudioController()
{
	
}

