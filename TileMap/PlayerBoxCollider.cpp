#include "PlayerBoxCollider.h"
#include "PlayerLogic.h"
#include "GUIRedOrbLogic.h"
#include "GUIRedOrbRender.h"
#include "CStateRyobeAttacking.h"
#include  <iostream>
PlayerBoxCollider::PlayerBoxCollider(GameObject* gameObject)
	: BoxColliderComponent(gameObject)
{
	GUIRedOrbObject = System::findGameObjectByName("GUIRedOrb");
	if(GUIRedOrbObject == nullptr)
		std::cout << "GUIRedOrb not found" << std::endl;
}
void PlayerBoxCollider::onCollisionEnter(Grid& grid, BoxColliderComponent* other)
{
	PlayerLogic* playerLogic = dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent);
	if(other->mGameObject->mLayerName == Layer::Enemy)
	{
		
	}

	
	

	if(other->mGameObject->mName == "RedOrb")
	{
		playerLogic->pickupRedOrb();
		dynamic_cast<GUIRedOrbLogic*>(GUIRedOrbObject->mLogicComponent)->showRedOrbGUI();
		System::removeGameObject(other->mGameObject);
	}

	if(other->mGameObject->mName == "GreenOrb")
	{
		playerLogic->pickupGreenOrb();
		//dynamic_cast<GUIRedOrbLogic*>(GUIRedOrbObject->mLogicComponent)->increaseRedOrbCount();
		System::removeGameObject(other->mGameObject);
	}

	
	if(other->mGameObject->mName == "RyobeAttackBox")
	{
		CStateRyobeAttacking* ryobeAttackingState = dynamic_cast<CStateRyobeAttacking*>(other->mGameObject->mParent->mState);
		if(ryobeAttackingState != nullptr)
		{
			playerLogic->hit(other->mGameObject->mParent, ryobeAttackingState->attackType);
		}

	}
	if(other->mGameObject->mName == "Dagger")
	{
		playerLogic->hit(other->mGameObject, Attacks::RYOBE_DAGGERTHROW);
		System::removeGameObject(other->mGameObject);
	}
	
}

void PlayerBoxCollider::onCollisionStay(Grid& grid, BoxColliderComponent* other)
{
	/*bool otherColliderRemoved = BoxColliderComponent::onCollisionStay(grid, other);
	
	if(otherColliderRemoved == true)
		return true;
		*/
	PlayerLogic* playerLogic = dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent);
	if(other->mGameObject->mName == "Lightning")
	{
		sf::FloatRect& otherBox = other->mGameObject->mBoxColliderComponent->getCollisionBox()->getGlobalBounds();
		sf::FloatRect& playerBox = mGameObject->mBoxColliderComponent->getCollisionBox()->getGlobalBounds();
		if(other->mGameObject->getPosition().x < mGameObject->getPosition().x)
		{
			float dist = (otherBox.left + otherBox.width) - playerBox.left ;
			playerLogic->move(dist, 0);
		}
		else
		{
			float dist = (playerBox.left + playerBox.width) - otherBox.left ;
			playerLogic->move(-dist, 0);
		}

	}
	/*if(other->mGameObject->mName == "Lightning")
	{
		if(other->mGameObject->getPosition().x < mGameObject->getPosition().x)
			playerLogic->move(playerLogic->getRunningSpeed(), 0);
		else
			playerLogic->move(-playerLogic->getRunningSpeed(), 0);

	}
	*/
	/*
	if(other->mGameObject->mName == "Ninja")
	{
		if(mCollisionBox.getGlobalBounds().intersects(other->getCollisionBox()->getGlobalBounds()))
		{
			//if(mGameObject->getPosition().x < other->mGameObject->getPosition().x
				//&& mGameObject->getPosition().y < other->mGameObject->getPosition().y)
			if(dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent)->getVelocity().y != 0)
			{
				if(mGameObject->getPosition().x < other->mGameObject->getPosition().x)
				{
					if(playerLogic->getVelocity().x != 0)
					{
						dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent)->move(- 1,0);
					}
					else
					{
						dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent)->move(-6,0);
					}
				
				}
				else
				{
					if(playerLogic->getVelocity().x != 0)
					{
						dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent)->move(1,0);
					}
					else
					{
						dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent)->move(+6,0);
					}
				}
			}
			if(dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent)->getVelocity().x != 0)
			{
				if(mGameObject->getPosition().x < other->mGameObject->getPosition().x)
				{
					float dist = other->getCollisionBox()->getGlobalBounds().left - (mCollisionBox.getGlobalBounds().left + mCollisionBox.getGlobalBounds().width);
					dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent)->move(dist,0);
				}
				else if(mGameObject->getPosition().x > other->mGameObject->getPosition().x)
				{
					float dist = (other->getCollisionBox()->getGlobalBounds().left + other->getCollisionBox()->getGlobalBounds().width) - (mCollisionBox.getGlobalBounds().left);
					dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent)->move(dist,0);
				}
			}
		}
	}*/

	
	
}

BoxColliderComponent* PlayerBoxCollider::onCollisionExit(Grid& grid, BoxColliderComponent* other)
{
	
	return nullptr;
}