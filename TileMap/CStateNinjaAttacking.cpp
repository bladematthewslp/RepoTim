#include "CStateNinjaAttacking.h"
#include "CStateNinjaStanding.h"
#include "CStateNinjaRunning.h"
#include "NinjaSlashBoxLogic.h"
#include "NinjaSlashBoxCollider.h"
#include "NinjaLogic.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "SpriteAnim.h"


CStateNinjaAttacking::CStateNinjaAttacking(GameObject* player) : CState("CStateNinjaAttacking")
	, slashBoxCreated(false)
{
	player->mRenderComponent->setAnimation(Attacks::NINJA_SLASH_GROUND);
	timer = 0;

	NinjaLogic* ninjaLogic = dynamic_cast<NinjaLogic*>(player->mLogicComponent);
	ninjaLogic->mSoundPlayer.play(SoundEffect::NinjaDaggerSwing);

}

void CStateNinjaAttacking::entry(GameObject* player)
{			
	dynamic_cast<NinjaLogic*>(player->mLogicComponent)->setVelocity(0,0);
}			
CState*	CStateNinjaAttacking::handleInput(GameObject* player, Grid& grid, const sf::Event& event)
{
	return this;
}
CState*	CStateNinjaAttacking::update(GameObject* player, sf::Time dt, Grid& grid)
{
	
	RenderComponent* ninjaRender = player->mRenderComponent;
	NinjaLogic* ninjaLogic = dynamic_cast<NinjaLogic*>(player->mLogicComponent);
	
	int currentFrame = ninjaRender->mSpriteSet[ninjaRender->currentAnim]->currentFrame;
	
	if(currentFrame == 7 && slashBoxCreated == false)
	{
		// create slash box game object
		GameObjectDesc slashBoxDesc("NinjaSlashBox", sf::RectangleShape(sf::Vector2f(100,100)), Layer::Enemy);
		GameObject* slashBox = std::unique_ptr<GameObject>(new GameObject(slashBoxDesc)).release();
		
		// add and configure logic component
		slashBox->addComponent(ComponentType::LogicComponent, std::unique_ptr<Component>(new NinjaSlashBoxLogic(slashBox)).release());
		NinjaSlashBoxLogic* slashBoxLogic = dynamic_cast<NinjaSlashBoxLogic*>(slashBox->mLogicComponent);
		slashBoxLogic->init(*player, ninjaLogic->getDirection(), Attacks::NINJA_SLASH_GROUND, 9);
		
		// add and configure box collider component
		slashBox->addComponent(ComponentType::BoxColliderComponent, std::unique_ptr<Component>(new NinjaSlashBoxCollider(slashBox)).release());
		slashBox->mBoxColliderComponent->setVisible(false);
		slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(100,60));

		

		slashBoxCreated = true;
	}
	if(currentFrame == 8)
	{
		slashBoxCreated = false;
	}
	float dist = std::abs( ninjaLogic->player->getPosition().x - player->getPosition().x);

	
	
	if(ninjaRender->runSpriteAnim(*player) == SpriteAnim::Status::SUCCESS)
	{
		timer++;
		//if(timer > 120)
		{
			if(dist > 125)
			{
				CState* newState = std::unique_ptr<CState>(new CStateNinjaRunning(player)).release();
				newState->entry(player);
				return newState;
			}
			else
			{
				CState* newState = std::unique_ptr<CStateNinjaStanding>(new CStateNinjaStanding(player)).release();
				return newState;
			}
		}

	
		
		//CState* newState = std::unique_ptr<CStateNinjaStanding>(new CStateNinjaStanding(player)).release();
		//return newState;
	}
	return this;
}