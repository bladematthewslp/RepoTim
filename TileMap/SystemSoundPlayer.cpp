#include "SystemSoundPlayer.h"

SystemSoundPlayer::SystemSoundPlayer()
	: SoundPlayer()
{

}

void SystemSoundPlayer::play(SoundEffect::ID effect)
{
	mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
	mSounds.back().play();
}

void SystemSoundPlayer::removeStoppedSounds()
{
	
	mSounds.remove_if( [] (const sf::Sound& s)
	{
		
		return s.getStatus() == sf::Sound::Stopped;
	} );
	
}