#include "AudioManager.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
{
	instance = this;

	audioClips.insert(std::pair<SoundTypes, AudioContainer*>(SoundTypes::Pickup, new AudioContainer("pickup.wav")));
}

void AudioManager::PlaySound(SoundTypes type)
{
	if (audioClips[type] == nullptr) {
		std::cout << "\nCouldn't play audio effect of type " << type << "! Forgot to initialize it?" << "\n";
		return;
	}
	audioClips[type]->PlaySound();
}