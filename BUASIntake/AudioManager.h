#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <iterator>
#include <map>

struct AudioContainer;

class AudioManager
{

public:
	enum SoundTypes
	{
        MainMusic,
		Pickup,

		Cleanup,
        Cleanup1,
        Cleanup2
	};

	AudioManager();
	static AudioManager* instance;

	void PlaySound(SoundTypes type);
    void PlayMusicSong(SoundTypes type, bool loop = true);

private:
    struct AudioContainer {
        sf::SoundBuffer* audioBuffer = nullptr;
        sf::Sound* sound = nullptr;

        // Default constructor
        AudioContainer() : audioBuffer(nullptr), sound(nullptr) {}

        // Parameterized constructor
        AudioContainer(sf::String fileLocation) {
            audioBuffer = new sf::SoundBuffer();

            if (audioBuffer->loadFromFile(fileLocation)) {
                sound = new sf::Sound();
                sound->setBuffer(*audioBuffer);
            }
        }

        void PlaySound() {
            sound->play();
        }
    };

    struct AudioMusicContainer 
    {
        sf::Music* music = nullptr;
        bool loopSong = true;

        // Default constructor
        AudioMusicContainer() : music(nullptr), loopSong(true) {}

        // Parameterized constructor
        AudioMusicContainer(sf::String fileLocation, bool loop = true) {
            music = new sf::Music();
            music->setLoop(loop);
            music->openFromFile(fileLocation);
        }

        void PlaySound() {
            music->play();
        }
    };

	std::map<SoundTypes, AudioContainer*> audioClips;
    std::map<SoundTypes, AudioMusicContainer*> musicClips;
};