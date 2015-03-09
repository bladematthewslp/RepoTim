#include "SoundEffectLogic.h"
#include "CState.h"


SoundEffectLogic::SoundEffectLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
{
	gameCharacter = System::findGameObjectByName("Player");
}


void SoundEffectLogic::update(Grid& grid)
{
	if(dynamic_cast<CState*>(gameCharacter->mState)->getName() != "AttackState" || mSoundPlayer.mSound.getStatus() == sf::Sound::Status::Stopped)
	{
		std::cout << "REMOVING" << std::endl;
		System::removeGameObject(mGameObject);
	}
}