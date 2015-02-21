#include "AttackBlockedState.h"
#include "StandingState.h"

AttackBlockedState::AttackBlockedState(GameObject* character)
	: CState("AttackBlockedState")
{
		character->mRenderComponent->setAnimation("DazedPart1");
}

CState* AttackBlockedState::update(GameObject* character, sf::Time dt, Grid& grid)
{

	character->mRenderComponent->runSpriteAnim(*character);



	if(character->mRenderComponent->getAnimStatus() == SpriteAnim::Status::SUCCESS)
	{
		CState* newState = std::unique_ptr<CState>(new StandingState(character)).release();
		newState->entry(character);
		return newState;

	}
	return this;
}