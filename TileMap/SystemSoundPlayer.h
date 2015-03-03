#pragma once

#include "SoundPlayer.h"

class SystemSoundPlayer : public SoundPlayer
{


public:
	SystemSoundPlayer();
	void play(SoundEffect::ID);
	void removeStoppedSounds();
};