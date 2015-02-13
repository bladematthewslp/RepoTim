#include "CStateRyobeAttacking.h"
#include "CStateRyobeStanding.h"
#include "RyobeLogic.h"
#include "DaggerLogic.h"


#define CREATE_DAGGER																													\
			GameObjectDesc daggerDesc("Dagger", sf::RectangleShape(sf::Vector2f(40,5)), Layer::Enemy, ComponentType::RenderComponent);	\
			GameObject* dagger = std::unique_ptr<GameObject>(new GameObject(daggerDesc)).release();										\
			dagger->addComponent(ComponentType::LogicComponent, std::unique_ptr<LogicComponent>(new DaggerLogic(dagger)).release());	\
			dagger->setPosition(character->getPosition().x - 0, character->getPosition().y -10);										\
			

CStateRyobeAttacking::CStateRyobeAttacking(GameObject* character)
	: CState("CStateRyobeAttackPunch")
	, daggerThrown(false)
	, attackType(-1)
{
	character->mRenderComponent->setAnimation("AttackReady");
}



CState* CStateRyobeAttacking::update(GameObject* character, sf::Time dt, Grid& grid)
{
	RyobeLogic* logic = dynamic_cast<RyobeLogic*>(character->mLogicComponent);
	
	character->mRenderComponent->runSpriteAnim(*character);
	if(character->mRenderComponent->currentAnim == "WeaponThrow")
	{
		if(character->mRenderComponent->mSpriteSet["WeaponThrow"]->currentFrame == 1 && daggerThrown == false)
		{
			
			CREATE_DAGGER;
			daggerThrown = true;
		}
	}


	if(character->mRenderComponent->getAnimStatus() == SpriteAnim::Status::SUCCESS)
	{
		if(character->mRenderComponent->currentAnim == "AttackReady")
		{
			if(attackType == RyobeAttack::Dagger)
			{
				character->mRenderComponent->setAnimation("WeaponThrow");
			}
			else
			{
				character->mRenderComponent->setAnimation("SwordAttack1");
			}
			
		}
		else
		{
			CState* newState = std::unique_ptr<CState>(new CStateRyobeStanding(character)).release();

			return newState;
		}
	}
	
	return this;

}

void CStateRyobeAttacking::entry(GameObject* character)
{
}