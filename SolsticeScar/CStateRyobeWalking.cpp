#include "CStateRyobeWalking.h"
#include "CStateRyobeAttackPunch.h"
#include "RyobeLogic.h"


CStateRyobeWalking::CStateRyobeWalking(GameObject* character)
	: CState("CStateRyobeWalking")
{

	character->mRenderComponent->setAnimation("Walking");

}
			
CState* CStateRyobeWalking::update(GameObject* character, sf::Time dt, Grid& grid)
{
	character->mRenderComponent->runSpriteAnim(*character);
	character->move(-1.5,0);
	

	float dist = std::abs(player->getPosition().x - character->getPosition().x);
	if(dist < 75)
	{
		CState* newState = std::unique_ptr<CState>(new CStateRyobeAttackPunch(character)).release();
		return newState;
	}

	return this;
}