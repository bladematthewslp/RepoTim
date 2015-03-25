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
	virtual void	stop();
	virtual void	play(SoundEffect::ID);
	void			load(SoundEffect::ID, std::string filename);
	void			removeStoppedSounds();
	static void		loadAllSounds();
	static void		unloadAllSounds();
	static			SoundBufferHolder mSoundBuffers;


	sf::Sound*		mSound;
protected:
	
	SoundEffect::ID		mCurrentSoundEffect;
	std::list<sf::Sound> mSounds;
	
	sf::SoundBuffer buff;
	

};