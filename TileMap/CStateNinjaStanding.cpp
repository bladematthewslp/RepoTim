#include "CStateNinjaStanding.h"
#include "CStateNinjaAttacking.h"
#include "CStateNinjaHit.h"
#include "CStateNinjaDead.h"
#include "CStateNinjaJumping.h"
#include "CStateNinjaRunning.h"
#include "NinjaLogic.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include <iostream>



CStateNinjaStanding::CStateNinjaStanding(GameObject* player) : CState("CStateNinjaStanding")
{
	player->mRenderComponent->setAnimation("Standing");
	delayTimer = 0;
}

void CStateNinjaStanding::entry(GameObject* player)
{			
	dynamic_cast<NinjaLogic*>(player->mLogicComponent)->setVelocity(0,0);//(true);		
}			
CState*	CStateNinjaStanding::handleInput(GameObject* player, const sf::Event& event)
{
	/*if(event.type == sf::Event::KeyPressed)
	{
		CState* newState = std::unique_ptr<CStateNinjaJumping>(new CStateNinjaJumping(player)).release();
		newState->entry(player);
		return newState;
	}*/
	return this;
}

CState*	CStateNinjaStanding::update(GameObject* character, sf::Time dt, Grid& grid)
{
	//character->mRenderComponent->runSpriteAnim(*character);
	NinjaLogic* logic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);

	character->mRenderComponent->runSpriteAnim(*character);
	static float spriteTimer = 0;

	float xDist = std::abs( logic->player->getPosition().x - character->getPosition().x);
	float yDist = std::abs(character->getPosition().y - logic->player->getPosition().y);

	spriteTimer++;

	if(xDist < 400 && yDist < 50)
	{
		//std::cout << delayTimer << std::endl;
		delayTimer++;
		if(delayTimer > 120)
		{
			spriteTimer = 0;
			CState* newState = std::unique_ptr<CState>(new CStateNinjaRunning(character)).release();
			newState->entry(character);
			return newState;
		}

	}
	return this;
}
