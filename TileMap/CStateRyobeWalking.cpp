#include "CStateRyobeWalking.h"
#include "RyobeLogic.h"


CStateRyobeWalking::CStateRyobeWalking(GameObject* character)
	: CState("CStateRyobeWalking")
{

	character->mRenderComponent->setAnimation("Walking");

}
				CState*		update(GameObject* character, sf::Time dt, Grid& grid);
CState* CStateRyobeWalking::update(GameObject* character, sf::Time dt, Grid& grid)
{
	character->mRenderComponent->runSpriteAnim(*character);
	character->move(-1.5,0);
	

	return this;
}