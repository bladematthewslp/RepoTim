#include "RyobeLogic.h"



RyobeLogic::RyobeLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
{
	mGameObject->mRenderComponent->setAnimation("Standing");

	
}

void RyobeLogic::update(Grid& grid)
{
	mGameObject->mRenderComponent->runSpriteAnim(*mGameObject);

}