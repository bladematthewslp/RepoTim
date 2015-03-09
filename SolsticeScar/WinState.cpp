#include "WinState.h"
#include "PlayerLogic.h"


WinState::WinState(GameObject* character)
	: CState("WinState")
{
	character->mRenderComponent->setAnimation("WinPoseBegin");
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(character->mLogicComponent);
	logic->mSoundPlayer.play(SoundEffect::DojiYouAreNotWorthy);
}


CState* WinState::update(GameObject* character, sf::Time dt, Grid& grid)
{
	if(character->mRenderComponent->runSpriteAnim(*character) == SpriteAnim::SUCCESS)
	{
		if(character->mRenderComponent->currentAnim == "WinPoseBegin")
		{
			character->mRenderComponent->setAnimation("WinPoseLoop");
		}
	}
	return this;
}