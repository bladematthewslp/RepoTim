#include "CStateRyobeAttackPunch.h"
#include "CStateRyobeStanding.h"


CStateRyobeAttackPunch::CStateRyobeAttackPunch(GameObject* character)
	: CState("CStateRyobeAttackPunch")
{

	character->mRenderComponent->setAnimation("AttackReady");
}



CState* CStateRyobeAttackPunch::update(GameObject* character, sf::Time dt, Grid& grid)
{
	character->mRenderComponent->runSpriteAnim(*character);

	if(character->mRenderComponent->getAnimStatus() == SpriteAnim::Status::SUCCESS)
	{
		if(character->mRenderComponent->currentAnim == "AttackReady")
		{
			character->mRenderComponent->setAnimation("Punch2");
		}
		else
		{
			CState* newState = std::unique_ptr<CState>(new CStateRyobeStanding(character)).release();

			return newState;
		}
	}
	
	return this;

}