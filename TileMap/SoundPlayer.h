#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include <list>

class SoundPlayer
{

public:
	SoundPlayer();

	void play(SoundEffect::ID);

	void removeStoppedSounds();
	
private:
	
	
	std::list<sf::Sound> mSounds;
	SoundBufferHolder mSoundBuffers;


};