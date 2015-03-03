#include "SoundEffectLogic.h"


SoundEffectLogic::SoundEffectLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
{

}


void SoundEffectLogic::update(Grid& grid)
{
	if(mSoundPlayer.mSound->getStatus() == sf::Sound::Status::Stopped)
	{
		std::cout << "REMOVING" << std::endl;
		System::removeGameObject(mGameObject);
	}
}