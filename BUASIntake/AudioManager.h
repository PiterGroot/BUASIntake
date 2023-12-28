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
		Pickup,
		Sink,
		Engine,
		Deposit
	};

	AudioManager();
	static AudioManager* instance;

	void PlaySound(SoundTypes type);

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

	std::map<SoundTypes, AudioContainer*> audioClips;
};