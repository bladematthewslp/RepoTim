#include "CStateRyobeStanding.h"
#include "CStateRyobeAttacking.h"
#include "CStateRyobeWalking.h"
#include "RyobeLogic.h"
#include <cmath>

CStateRyobeStanding::CStateRyobeStanding(GameObject* character)
	: CState("CStateRyobeStanding")
	, timer(0)
	, startTimer(false)
{
	
	character->mRenderComponent->setAnimation("Standing");

}


CState*	CStateRyobeStanding::update(GameObject* character, sf::Time dt, Grid& grid)
{
	RyobeLogic* logic = dynamic_cast<RyobeLogic*>(character->mLogicComponent);

	
	character->mRenderComponent->runSpriteAnim(*character);
	timer += dt.asSeconds();
	float dist = std::abs(player->getPosition().x - character->getPosition().x);


	if(timer > 1.5)
	{
		CStateRyobeAttacking* newState = std::unique_ptr<CStateRyobeAttacking>(new CStateRyobeAttacking(character)).release();
		
		int health = logic->getHealth();
		
		if(dist < 200)
		{
			if(health >= 75)
				newState->attackType = Attacks::RYOBE_SWORDATTACK;
			else //if(health >= 50)
				newState->attackType = Attacks::RYOBE_TELEPORT;
		}
		else if(dist >= 200)
		{
			if(health >= 75)
				newState->attackType = Attacks::RYOBE_DAGGERTHROW;
			else //if(health >= 40)
				newState->attackType = Attacks::RYOBE_EMBRACER;
		}

		newState->entry(character);
		return newState;
	}
	/*
	if(dist < 175)
	{
		startTimer = true;
		CState* newState = std::unique_ptr<CState>(new CStateRyobeWalking(character)).release();
		return newState;
		//character->mRenderComponent->setAnimation("Teleport");

	}
	*/



	return this;
}