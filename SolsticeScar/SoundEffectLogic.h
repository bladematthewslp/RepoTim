#pragma once

#include "LogicComponent.h"
#include "SoundPlayer.h"

class SoundEffectLogic : public LogicComponent
{
	GameObject* gameCharacter;
public:
	SoundEffectLogic(GameObject* gameObject);
	void update(Grid& grid);

	SoundPlayer		mSoundPlayer;


};