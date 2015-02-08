#include "CStateRyobeStanding.h"
#include "CStateRyobeWalking.h"
#include <cmath>

CStateRyobeStanding::CStateRyobeStanding(GameObject* character)
	: CState("CStateRyobeStanding")
{
	
	character->mRenderComponent->setAnimation("Blocking");

}


CState*	CStateRyobeStanding::update(GameObject* character, sf::Time dt, Grid& grid)
{
	character->mRenderComponent->runSpriteAnim(*character);

	float dist = std::abs(player->getPosition().x - character->getPosition().x);

	if(dist < 175)
	{
		CState* newState = std::unique_ptr<CState>(new CStateRyobeWalking(character)).release();
		return newState;
		//character->mRenderComponent->setAnimation("Teleport");

	}



	return this;
}