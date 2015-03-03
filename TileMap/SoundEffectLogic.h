#pragma once

#include "LogicComponent.h"
#include "SoundPlayer.h"

class SoundEffectLogic : public LogicComponent
{

public:
	SoundEffectLogic(GameObject* gameObject);
	void update(Grid& grid);

	SoundPlayer		mSoundPlayer;


};