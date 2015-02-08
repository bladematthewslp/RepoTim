#include "DazedState.h"
#include "StandingState.h"

DazedState::DazedState(GameObject* character)
	: CState("DazedState")
{
	character->mRenderComponent->setAnimation("DazedPart1");
	dazedTimer = 0;
}


CState* DazedState::update(GameObject* character, sf::Time dt, Grid& grid)
{
	character->mRenderComponent->runSpriteAnim(*character);
	dazedTimer += sf::seconds(1.0f/60.0f).asSeconds();
	std::cout << dazedTimer << std::endl;
	if(character->mRenderComponent->currentAnim == "DazedPart1")
	{
		if(character->mRenderComponent->getAnimStatus() == SpriteAnim::Status::SUCCESS)
		{
			character->mRenderComponent->setAnimation("DazedPart2");
		}
	}
	else
	{
		if(dazedTimer > 5)
		{
			CState* newState = std::unique_ptr<CState>(new StandingState(character)).release();
			newState->entry(character);
			return newState;
		}
	}
	return this;
}