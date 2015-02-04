#include "CStateNinjaHit.h"
#include "NinjaRender.h"
#include "NinjaLogic.h"
#include "CStateNinjaStanding.h"
#include <iostream>


CStateNinjaHit::CStateNinjaHit(GameObject* character) : CState("CStateNinjaHit")
	, isAirborne(false)
	, damageTimer(0)
	, mHitStartingVelocityX(0)
	, mLaunchSpeed(-13)
{
	
	
}

CState* CStateNinjaHit::handleInput(GameObject* character, const sf::Event& event)
{
	// why does ninja need input?

	return this;
}

CState* CStateNinjaHit::update(GameObject* character, sf::Time dt, Grid& grid)
{
	
	
	NinjaRender* render = dynamic_cast<NinjaRender*>(character->getRenderComponent());
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	
	
	
	render->runSpriteAnim(*character) ;
	
	
	sf::Vector2f velocity = logic->getVelocity();
	switch(logic->getDirection())
	{
		case Direction::Right:
			if(mHitStartingVelocityX < 0)
			{
				velocity.x += logic->getDirection() * 0.05f;
				if(velocity.x > 0)
					velocity.x = 0;
			}
			else if(mHitStartingVelocityX > 0)
			{
				velocity.x -= logic->getDirection() * 0.05f;
				if(velocity.x < 0)
					velocity.x = 0;
			}
			break;
		case Direction::Left:				// if facing left...
			if(mHitStartingVelocityX > 0)	// ...and ninja it hit to the right...
			{
				velocity.x -= 0.05f;			// ...add an opposing left force
				if(velocity.x < 0)
					velocity.x = 0;
			}
			else if(mHitStartingVelocityX < 0)
			{
				velocity.x += 0.05f;
				if(velocity.x > 0)
					velocity.x = 0;
			}
			break;

	}
		
		logic->setVelocityX(velocity.x);
		logic->move(logic->getVelocity());
		if(damageTimer == 60)
		{
			CState* newState = std::unique_ptr<CState>(new CStateNinjaStanding(character)).release();
			newState->entry(character);
			return newState;


		}
	
	/*
	if(damageTimer == 90)
	{
		damageTimer = 0;
		CState* state = std::unique_ptr<CState>(new CStateNinjaStanding(character)).release();
		state->entry(character);
		return state;
	}
	*/

	damageTimer++;
	return this;
}

void CStateNinjaHit::entry(GameObject* character, AttackType attackType)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	mHitStartingVelocityX = logic->getVelocity().x;
	character->getRenderComponent()->setAnimation("Hit");
	
}

void CStateNinjaHit::successiveHit(GameObject* character, AttackType attackType)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	damageTimer = 0;
	mHitStartingVelocityX = logic->getVelocity().x;
	if(character->getRenderComponent()->currentAnim == "Hit")
		character->getRenderComponent()->setAnimation("Hit2");
	else
		character->getRenderComponent()->setAnimation("Hit");
	if(attackType.mCanLaunch == true)
	{
		dynamic_cast<NinjaLogic*>(character->mLogicComponent)->setVelocityY(mLaunchSpeed);
		isAirborne = true;
		std::cout << isAirborne << std::endl;
	}
}