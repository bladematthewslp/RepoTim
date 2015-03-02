#include "CStateNinjaHitAir.h"
#include "NinjaRender.h"
#include "NinjaLogic.h"
#include "CStateNinjaStanding.h"
#include <iostream>


const float MAX_FALLING_SPEED = 4;

CStateNinjaHitAir::CStateNinjaHitAir(GameObject* character) : CState("CStateNinjaHitAir")
	, isAirborne(false)
	, damageTimer(0)
	, mHitStartingVelocityX(0)
	//, mLaunchSpeed(-13)
{
	mAirSpeed = -13;
	
}

CState* CStateNinjaHitAir::handleInput(GameObject* character, const sf::Event& event)
{
	// why does ninja need input?

	return this;
}

CState* CStateNinjaHitAir::update(GameObject* character, sf::Time dt, Grid& grid)
{
	
	
	NinjaRender* render = dynamic_cast<NinjaRender*>(character->getRenderComponent());
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	
	
	render->runSpriteAnim(*character) ;
	

 	sf::Vector2f vel = logic->getVelocity();
	
	if(vel.y >= -3 && vel.y < 0)
		mAirSpeed += 0.22f;
	else
		mAirSpeed += 0.63f;

	if(mAirSpeed > MAX_FALLING_SPEED)
		mAirSpeed = MAX_FALLING_SPEED;

	

	
	logic->setVelocityY(mAirSpeed);
	logic->move(logic->getVelocity());
	
	if(grid.checkCollisionAbove(character->mBoxColliderComponent) == true)
	{
		logic->setVelocityY(1);
		logic->move(0, logic->getVelocity().y);
	}
	if(grid.checkCollisionBelow(character->mBoxColliderComponent) == true   )
	{
		logic->move(sf::Vector2f(0, -grid.playerPosition.y));
		
		CState* newState = std::unique_ptr<CState>(new CStateNinjaStanding(character)).release();
		newState->entry(character);
		return newState;
	}


	damageTimer++;
	return this;
}

void CStateNinjaHitAir::entry(GameObject* character, AttackType attackType)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	//mHitStartingVelocityX = logic->getVelocity().x;
	//if(attackType.mCanLaunch == true)
	//{
		dynamic_cast<NinjaLogic*>(character->mLogicComponent)->setVelocityY(mLaunchSpeed);
	//	isAirborne = true;
	//	std::cout << isAirborne << std::endl;
	character->getRenderComponent()->setAnimation("AirHit1");
//	logic->setVelocityY(0);
	//}
	//else
	//{
		//character->getRenderComponent()->setAnimation("Hit");
	//}
	
}

void CStateNinjaHitAir::successiveHit(GameObject* character, AttackType attackType)
{
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	damageTimer = 0;
	mAirSpeed = -3;
	logic->setVelocityY(mAirSpeed);
	
	if(character->getRenderComponent()->currentAnim == "AirHit1")
		character->getRenderComponent()->setAnimation("AirHit2");
	else
		character->getRenderComponent()->setAnimation("AirHit1");
	
	
	
	dynamic_cast<NinjaLogic*>(character->mLogicComponent)->setVelocityY(mAirSpeed);
}