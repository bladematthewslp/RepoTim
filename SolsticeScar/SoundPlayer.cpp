#include "SoundPlayer.h"
#include <iostream>
SoundBufferHolder SoundPlayer::mSoundBuffers;

SoundPlayer::SoundPlayer()
	: 
	//, mSound(nullptr)
	 mCurrentSoundEffect(SoundEffect::None)
{
	
	mSound = nullptr;//std::unique_ptr<sf::Sound>(new sf::Sound(mSoundBuffers.get(SoundEffect::None))).release();
	
}

void SoundPlayer::loadAllSounds()
{

	mSoundBuffers.load(SoundEffect::None,				"SoundEffects/silence.wav");
	mSoundBuffers.load(SoundEffect::ChargeUp,			"SoundEffects/ChargeUp.wav");
	mSoundBuffers.load(SoundEffect::DojiChopperStyle,	"SoundEffects/DojiChopperStyle.wav");
	//mSoundBuffers.load(SoundEffect::DojiChopperStyleSoundEffect, "SoundEffects/DojiChopperStyleSoundEffect.wav");
	mSoundBuffers.load(SoundEffect::DojiDead,			"SoundEffects/DojiDead.wav");
	mSoundBuffers.load(SoundEffect::DojiExpel,			"SoundEffects/DojiExpel.wav");
	mSoundBuffers.load(SoundEffect::DojiHailBringerDescending, "SoundEffects/DojiHailBringerDescending2.wav");
	mSoundBuffers.load(SoundEffect::DojiHailBringerLanding, "SoundEffects/DojiHailBringerLanding.wav");
	mSoundBuffers.load(SoundEffect::DojiHit,			"SoundEffects/DojiHit.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwing1,	"SoundEffects/DojiSwordSwing1.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwing2,	"SoundEffects/DojiSwordSwing2.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwing3,	"SoundEffects/DojiSwordSwing3.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwingAir,	"SoundEffects/DojiSwordSwingAir.wav");
	mSoundBuffers.load(SoundEffect::DojiSwordSwingQuick,"SoundEffects/DojiSwordSwingQuick.wav");
	mSoundBuffers.load(SoundEffect::DojiImpact,			"SoundEffects/DojiImpact.wav");
	mSoundBuffers.load(SoundEffect::DojiYouAreNotWorthy,"SoundEffects/DojiYouAreNotWorthy.wav");
	mSoundBuffers.load(SoundEffect::ElectricCurrent,	"SoundEffects/ElectricCurrent.wav");
	mSoundBuffers.load(SoundEffect::Jump,				"SoundEffects/Jump.wav");
	mSoundBuffers.load(SoundEffect::Landing,			"SoundEffects/Landing.wav");
	mSoundBuffers.load(SoundEffect::NinjaDaggerSwing,	"SoundEffects/NinjaDaggerSwing.wav");
	mSoundBuffers.load(SoundEffect::NinjaHit,			"SoundEffects/NinjaHit.wav");
	mSoundBuffers.load(SoundEffect::Running1,			"SoundEffects/Running1.wav");
	mSoundBuffers.load(SoundEffect::Running2,			"SoundEffects/Running2.wav");
	mSoundBuffers.load(SoundEffect::RyobeComeAndGetMe,	"SoundEffects/RyobeComeAndGetMe.wav");
	mSoundBuffers.load(SoundEffect::RyobeDead,			"SoundEffects/RyobeDead.wav");
	mSoundBuffers.load(SoundEffect::RyobeEmbracer,		"SoundEffects/RyobeEmbracer.wav");
	mSoundBuffers.load(SoundEffect::RyobeFellCrescent,	"SoundEffects/RyobeFellCrescent.wav");
	mSoundBuffers.load(SoundEffect::RyobeFire,			"SoundEffects/RyobeFire.wav");
	mSoundBuffers.load(SoundEffect::RyobeKnifeThrow,	"SoundEffects/RyobeKnifeThrow.wav");
	mSoundBuffers.load(SoundEffect::RyobeSwordAttack,	"SoundEffects/RyobeSwordAttack.wav");
	mSoundBuffers.load(SoundEffect::RyobeStandStill,	"SoundEffects/RyobeStandStill.wav");
	mSoundBuffers.load(SoundEffect::Teleport,			"SoundEffects/Teleport.wav");
	
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
	

	if(mSound != nullptr && mSound->getStatus() == sf::Sound::Status::Playing)//mSound != nullptr)
	{
		//std::cout << "SoundPlayer::play : about to play. stopping current sound." << std::endl;
		mSound->stop();
		delete mSound;
	}
	mCurrentSoundEffect = effect;
	
	
	mSound = std::unique_ptr<sf::Sound>(new sf::Sound(mSoundBuffers.get(effect))).release();
	
	mSound->play();
}

void SoundPlayer::stop()
{
	if(mSound != nullptr)
	{
		mSound->stop();
		mSound = nullptr;
	};
}

void SoundPlayer::removeStoppedSounds()
{
	if( mSound != nullptr && mSound->getStatus() == sf::Sound::Status::Stopped)
	{
		delete mSound;
		mSound = nullptr;
	}
	//std::cout << "removing" << std::endl;
	
	/*
	if(mSound != nullptr mSound->getStatus() == sf::Sound::Stopped)
	{
		//std::cout << mSound->getStatus() << std::endl;
		delete mSound;
		mSound = nullptr;
	}*/

	/*
	mSounds.remove_if( [] (const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	} );
	*/
}