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
	
	character->mRenderComponent->setAnimation("Charge2");

}


CState*	CStateRyobeStanding::update(GameObject* character, sf::Time dt, Grid& grid)
{
	RyobeLogic* logic = dynamic_cast<RyobeLogic*>(character->mLogicComponent);

	
	character->mRenderComponent->runSpriteAnim(*character);
	timer += dt.asSeconds();
	float dist = std::abs(player->getPosition().x - character->getPosition().x);


	if(timer > 3)
	{
		CStateRyobeAttacking* newState = std::unique_ptr<CStateRyobeAttacking>(new CStateRyobeAttacking(character)).release();
		if(dist < 200)
		{
			newState->attackType = CStateRyobeAttacking::RyobeAttack::SwordAttack;
		}
		else if(dist >= 200)
		{
			newState->attackType = CStateRyobeAttacking::RyobeAttack::Dagger;
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