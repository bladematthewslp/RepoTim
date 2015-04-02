#include "CStateNinjaFalling.h"
#include "CStateNinjaStanding.h"
#include "CStateNinjaRunning.h"
#include "NinjaLogic.h"


CStateNinjaFalling::CStateNinjaFalling(GameObject* character)
	: CState("CStateNinjaFalling")
{
	character->mRenderComponent->setAnimation("Falling");

	if(character->mState != nullptr)
	{
		previousStateName = character->mState->getName();
	}
}


void		CStateNinjaFalling::entry(GameObject* character)
{

}
CState*		CStateNinjaFalling::handleInput(GameObject* character, const sf::Event& event)
{
	return this;
}

CState*		CStateNinjaFalling::update(GameObject* character, sf::Time dt, Grid& grid)
{
	character->getRenderComponent()->runSpriteAnim(*character);

	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	logic->move(0, 3);
	if(grid.checkCollisionBelow(character->mBoxColliderComponent) == true   )
	{
		logic->move(sf::Vector2f(0, -grid.playerPosition.y));
		if(previousStateName == "CStateNinjaRunning")
		{
			CState* newState = std::unique_ptr<CState>(new CStateNinjaRunning(character)).release();
			newState->entry(character);
			return newState;
		}
		else
		{
			CState* newState = std::unique_ptr<CState>(new CStateNinjaStanding(character)).release();
			newState->entry(character);
			return newState;
		}
		/*
		if(previousStateName == "CStateNinjaStanding")
		{
			CState* newState = std::unique_ptr<CState>(new CStateNinjaStanding(character)).release();
			newState->entry(character);
			return newState;
		}
		else if(previousStateName == "CStateNinjaRunning")
		{
			CState* newState = std::unique_ptr<CState>(new CStateNinjaRunning(character)).release();
			newState->entry(character);
			return newState;
		}
		*/
	}

	return this;
}