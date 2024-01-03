#include "AudioManager.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
{
	instance = this;
	sf::String audioPath = "Resources/Audio/";

	musicClips.insert(std::pair<SoundTypes, AudioMusicContainer*>(SoundTypes::MainMusic, new AudioMusicContainer(audioPath + "music.wav")));

	audioClips.insert(std::pair<SoundTypes, AudioContainer*>(SoundTypes::Pickup, new AudioContainer(audioPath + "pickup.wav")));
	audioClips.insert(std::pair<SoundTypes, AudioContainer*>(SoundTypes::Cleanup, new AudioContainer(audioPath + "cleanup.wav")));
	audioClips.insert(std::pair<SoundTypes, AudioContainer*>(SoundTypes::Cleanup1, new AudioContainer(audioPath + "cleanup1.wav")));
	audioClips.insert(std::pair<SoundTypes, AudioContainer*>(SoundTypes::Cleanup2, new AudioContainer(audioPath + "cleanup2.wav")));
	audioClips.insert(std::pair<SoundTypes, AudioContainer*>(SoundTypes::Deny, new AudioContainer(audioPath + "deny.wav")));

	PlayMusicSong(SoundTypes::MainMusic);
}

void AudioManager::PlaySound(SoundTypes type)
{
	if (audioClips[type] == nullptr) {
		std::cout << "\nCouldn't play audio effect of type " << type << "! Forgot to initialize it?" << "\n";
		return;
	}
	audioClips[type]->PlaySound();
}

void AudioManager::PlayMusicSong(SoundTypes type, bool loop)
{
	if (musicClips[type] == nullptr) {
		std::cout << "\nCouldn't play music song of type " << type << "! Forgot to initialize it?" << "\n";
		return;
	}
	musicClips[type]->PlaySound();
}