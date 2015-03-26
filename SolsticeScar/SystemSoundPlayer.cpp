#include "SystemSoundPlayer.h"

SystemSoundPlayer::SystemSoundPlayer()
	: SoundPlayer()
{

}

void SystemSoundPlayer::play(SoundEffect::ID effect, bool loop)
{
	sf::Sound newSound(mSoundBuffers.get(effect));
	newSound.setLoop(loop);
	mSounds.push_back(newSound);
	mSounds.back().play();
}

void SystemSoundPlayer::removeStoppedSounds()
{
	
	mSounds.remove_if( [] (const sf::Sound& s)
	{
		
		return s.getStatus() == sf::Sound::Stopped;
	} );
	
}