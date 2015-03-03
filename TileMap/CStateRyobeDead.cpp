#include "CStateRyobeDead.h"
#include "RyobeLogic.h"

CStateRyobeDead::CStateRyobeDead(GameObject* character)
	: CState("CStateRyobeDead")
	, mVelocity(-5.0f, 0)
{
	RyobeLogic* logic = dynamic_cast<RyobeLogic*>(character->mLogicComponent);
	character->mRenderComponent->setAnimation("Dead");

	logic->mSoundPlayer.play(SoundEffect::RyobeDead);
}

CState* CStateRyobeDead::update(GameObject* character, sf::Time dt, Grid& grid)
{
	RyobeLogic* logic = dynamic_cast<RyobeLogic*>(character->mLogicComponent);
	character->mRenderComponent->runSpriteAnim(*character);
	mVelocity.x += 0.1f;
	if(mVelocity.x >= 0)
		mVelocity.x = 0;

	logic->setVelocityX(mVelocity.x * logic->getDirection());
	logic->move(logic->getVelocity());

	return this;
}