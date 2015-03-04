#include "SoundPlayer.h"
#include <iostream>
SoundBufferHolder SoundPlayer::mSoundBuffers;

SoundPlayer::SoundPlayer()
	: mSounds()
	, mSound(nullptr)
	, mCurrentSoundEffect(SoundEffect::None)
{
	
	
	
}

void SoundPlayer::loadAllSounds()
{
	mSoundBuffers.load(SoundEffect::ChargeUp,		"SoundEffects/ChargeUp.wav");
	mSoundBuffers.load(SoundEffect::DojiDead, "SoundEffects/DojiDead.wav");
	mSoundBuffers.load(SoundEffect::DojiHit, "SoundEffects/DojiHit.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwing1, "SoundEffects/DojiSwordSwing1.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwing2, "SoundEffects/DojiSwordSwing2.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwing3, "SoundEffects/DojiSwordSwing3.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwingAir, "SoundEffects/DojiSwordSwingAir.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwingQuick, "SoundEffects/DojiSwordSwingQuick.wav");
	mSoundBuffers.load(SoundEffect::DojiImpact,			"SoundEffects/DojiImpact.wav");
	mSoundBuffers.load(SoundEffect::ElectricCurrent,			"SoundEffects/ElectricCurrent.wav");
	mSoundBuffers.load(SoundEffect::NinjaDaggerSwing,			"SoundEffects/NinjaDaggerSwing.wav");
	mSoundBuffers.load(SoundEffect::RyobeComeAndGetMe, "SoundEffects/RyobeComeAndGetMe.wav");
	mSoundBuffers.load(SoundEffect::RyobeDead,		"SoundEffects/RyobeDead.wav");
	mSoundBuffers.load(SoundEffect::RyobeEmbracer,	"SoundEffects/RyobeEmbracer.wav");
	mSoundBuffers.load(SoundEffect::RyobeFellCrescent,		"SoundEffects/RyobeFellCrescent.wav");
	mSoundBuffers.load(SoundEffect::RyobeFire,		"SoundEffects/RyobeFire.wav");
	mSoundBuffers.load(SoundEffect::RyobeKnifeThrow, "SoundEffects/RyobeKnifeThrow.wav");
	mSoundBuffers.load(SoundEffect::RyobeSwordAttack, "SoundEffects/RyobeSwordAttack.wav");
	mSoundBuffers.load(SoundEffect::RyobeStandStill, "SoundEffects/RyobeStandStill.wav");
	mSoundBuffers.load(SoundEffect::Teleport, "SoundEffects/Teleport.wav");
	
}

void SoundPlayer::unloadAllSounds()
{
	mSoundBuffers.mResourceMap.clear();
}

void SoundPlayer::load(SoundEffect::ID effect, std::string filename)
{
	mSoundBuffers.load(effect, filename);

}

void SoundPlayer::play(SoundEffect::ID effect)
{
	/*
	sf::SoundBuffer& buff = mSoundBuffers.get(mCurrentSoundEffect);
	sf::Sound newSound(mSoundBuffers.get(effect));
	if(newSound.getBuffer() == &buff)
	{

	}
	/*
	mSounds.remove_if( [] (const sf::Sound& s)
	{
		
		return s.getStatus() == sf::Sound::Stopped;
	} );
	
	mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
	mSounds.back().play();
	*/

	if(mSound != nullptr)
	{
		//std::cout << "SoundPlayer::play : about to play. stopping current sound." << std::endl;
		mSound->stop();
	}
	mCurrentSoundEffect = effect;
	
	buff = sf::SoundBuffer(mSoundBuffers.get(effect));
	mSound = std::unique_ptr<sf::Sound>(new sf::Sound(mSoundBuffers.get(effect))).release();
	mSound->play();
	/*
	std::list<sf::Sound>::iterator iter;
	for(iter = mSounds.begin(); iter != mSounds.end(); ++iter)
	{
		if(iter == m
	}
	if(sf::Sound(mSoundBuffers.get(mCurrentSoundEffect)).getStatus() == sf::SoundSource::Status::Playing)
	{
		
		mSounds
	}
	mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
	mSounds.back().play();*/
}

void SoundPlayer::removeStoppedSounds()
{
	//std::cout << "removing" << std::endl;
	if(mSound != nullptr && mSound->getStatus() == sf::Sound::Stopped)
	{
		//std::cout << mSound->getStatus() << std::endl;
		delete mSound;
		mSound = nullptr;
	}
	/*
	mSounds.remove_if( [] (const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	} );
	*/
}