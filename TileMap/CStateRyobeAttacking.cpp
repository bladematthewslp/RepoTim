#include "CStateRyobeAttacking.h"
#include "CStateRyobeStanding.h"
#include "RyobeAttackBoxLogic.h"
#include "RyobeLogic.h"
#include "DaggerLogic.h"



#define CREATE_DAGGER																													\
			GameObjectDesc daggerDesc("Dagger", sf::RectangleShape(sf::Vector2f(40,5)), Layer::Enemy, ComponentType::RenderComponent);	\
			GameObject* dagger = std::unique_ptr<GameObject>(new GameObject(daggerDesc)).release();										\
			dagger->addComponent(ComponentType::LogicComponent, std::unique_ptr<LogicComponent>(new DaggerLogic(dagger)).release());	\
			dagger->setPosition(character->getPosition().x - 0, character->getPosition().y -10);										\
			

#define CREATE_ATTACK_BOX																												\
			GameObjectDesc slashBoxDesc("RyobeAttackBox",sf::RectangleShape(sf::Vector2f(100,130)),	Layer::Enemy);						\
			GameObject* slashBox = std::unique_ptr<GameObject>(new GameObject(slashBoxDesc)).release();									\
			slashBox->addComponent(ComponentType::LogicComponent, std::unique_ptr<LogicComponent>(new RyobeAttackBoxLogic(slashBox)).release());\
			slashBox->addComponent(ComponentType::BoxColliderComponent);																\
			//slashBox->mBoxColliderComponent->setVisible(true);																			\


CStateRyobeAttacking::CStateRyobeAttacking(GameObject* character)
	: CState("CStateRyobeAttacking")
	, daggerThrown(false)
	, attackType("")
	, timer(0)
	, embracerSpeed(10)
	, teleporting(false)
	, teleportTimer(0)
	, chargeLoopCounter(0)
	, embracerAttackBoxCreated(false)
{
	
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
	else if(character->mRenderComponent->currentAnim == "EmbracerPart2" 
		&& character->mRenderComponent->mSpriteSet["EmbracerPart2"]->currentFrame >= 3)
	{
		embracerSpeed -= 0.2f;
		if(embracerSpeed < 0)
			embracerSpeed = 0;
		logic->setVelocityX(embracerSpeed * logic->getDirection());
		
		logic->move(logic->getVelocity().x , 0);

		if(grid.checkCollisionLeft(character->mBoxColliderComponent) == true)
		{
			std::cout << logic->getVelocity().x << std::endl;
			logic->move(-logic->getVelocity().x, 0);
		}
		if( embracerAttackBoxCreated == false)
		{
			CREATE_ATTACK_BOX;
			slashBox->mBoxColliderComponent->setSize(40,30);
			slashBox->setPosition(80 * logic->getDirection(),-20);
			character->addChild(slashBox);
			embracerAttackBoxCreated = true;
		}
	}
	

	if(character->mRenderComponent->getAnimStatus() == SpriteAnim::Status::SUCCESS)
	{
		if(character->mRenderComponent->currentAnim == "AttackReady")
		{
			if(attackType == Attacks::RYOBE_DAGGERTHROW)
			{
				character->mRenderComponent->setAnimation("WeaponThrow");
			}
			else if(attackType == Attacks::RYOBE_EMBRACER)
			{
				character->mRenderComponent->setAnimation("Charge2");
			}
			else
			{
				character->mRenderComponent->setAnimation("SwordAttack1");
				CREATE_ATTACK_BOX;
				slashBox->mBoxColliderComponent->setSize(45,65);
				slashBox->setPosition(50 * logic->getDirection(),-60);
				character->addChild(slashBox);
				
			}
			
		}
		else if(character->mRenderComponent->currentAnim == "Teleport")
		{
			// set teleporting to true and translate to position out of view
			teleporting = true;
			character->setPosition(-100,-100);
		}
		else if(character->mRenderComponent->currentAnim == "Charge2")
		{
			chargeLoopCounter++;
			if(chargeLoopCounter == 6)
				character->mRenderComponent->setAnimation("EmbracerPart1");
		}
		else if(character->mRenderComponent->currentAnim == "EmbracerPart1")
		{
			timer++;
			if(timer > 30)
			{
				character->mRenderComponent->setAnimation("EmbracerPart2");
			}
		}
		else
		{
			CState* newState = std::unique_ptr<CState>(new CStateRyobeStanding(character)).release();
			return newState;
		}
	}

	if(teleporting == true)
	{
		// increate teleport timer
		teleportTimer += dt.asSeconds();

		// set the time limit to appear
		float timeToAppear;
		if(logic->getHealth() > 35)
			timeToAppear = 3;
		else
			timeToAppear = 0;

		if(teleportTimer >= timeToAppear)
		{
			GameObject* player = System::findGameObjectByName("Player");
			if(player->getPosition().x > 200)
			{
				if(player->getPosition().x < 900)
					character->setPosition(player->getPosition().x + 80, 568);
				else
					character->setPosition(player->getPosition().x - 80, 568);
			}
			else
				character->setPosition(player->getPosition().x + 80, 568);


			logic->updateDirection();
			character->mRenderComponent->setAnimation("TeleportSwordAttack1");

			CREATE_ATTACK_BOX;
			slashBox->mBoxColliderComponent->setSize(45,65);
			slashBox->setPosition(50 * logic->getDirection(),-60);
			character->addChild(slashBox);
			teleportTimer = 0.0f;
			teleporting = false;
		}
	}
	
	return this;

}

void CStateRyobeAttacking::entry(GameObject* character)
{
	if(attackType == Attacks::RYOBE_EMBRACER)
	{
		character->mRenderComponent->setAnimation("Charge2");
	}
	else if(attackType == Attacks::RYOBE_TELEPORT)
	{
		character->mRenderComponent->setAnimation("Teleport");
		attackType = Attacks::RYOBE_SWORDATTACK;
	}
	else
	{
		character->mRenderComponent->setAnimation("AttackReady");
	}
	
}

bool CStateRyobeAttacking::isTeleporting()
{
	return teleporting; 
}