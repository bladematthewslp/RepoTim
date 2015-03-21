#include "CStateRyobeBlocking.h"
#include "DazedState.h"

CStateRyobeBlocking::CStateRyobeBlocking(GameObject* character)
	: CState("CStateRyobeBlocking")
{

	character->mRenderComponent->setAnimation("Blocking");
	player->mState = std::unique_ptr<CState>(new DazedState(player)).release();
}

CState* CStateRyobeBlocking::update(GameObject* character, sf::Time dt, Grid& grid)
{
	character->mRenderComponent->runSpriteAnim(*character);


	return this;
}