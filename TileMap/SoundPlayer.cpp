#include "SoundPlayer.h"


SoundPlayer::SoundPlayer()
	: mSoundBuffers()
	, mSounds()
{
	mSoundBuffers.load(SoundEffect::DojiSwordSwing1, "SoundEffects/DojiSwordSwing1.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwing2, "SoundEffects/DojiSwordSwing2.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwing3, "SoundEffects/DojiSwordSwing3.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwingQuick, "SoundEffects/DojiSwordSwingQuick.wav");

}

void SoundPlayer::play(SoundEffect::ID effect)
{
	
	mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
	mSounds.back().play();
}

void SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if( [] (const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	} );

}