#include "BattleReadyState.h"
#include "StandingState.h"



BattleReadyState::BattleReadyState(GameObject* character)
	: CState("BattleReadyState")
{
	timer = 0;
	maxTime = 9999999;
	character->mRenderComponent->setAnimation("BattleReadyBegin");
}

CState* BattleReadyState::update(GameObject* character, sf::Time dt, Grid& grid)
{
	if( character->mRenderComponent->runSpriteAnim(*character) == SpriteAnim::SUCCESS)
	{
		if(character->mRenderComponent->currentAnim == "BattleReadyBegin")
		{
			character->mRenderComponent->setAnimation("BattleReadyLoop");
		}
		else if(character->mRenderComponent->currentAnim == "BattleReadyEnding")
		{
			CState* newState = std::unique_ptr<CState>(new StandingState(character)).release();
			newState->entry(character);
			return newState;
		}
	}
	timer += dt.asSeconds();
	if(timer >= maxTime)
	{
		character->mRenderComponent->setAnimation("BattleReadyEnding");
	}
	
	return this;

}

void BattleReadyState::setMaxTime(float num)
{
	maxTime = num;
}