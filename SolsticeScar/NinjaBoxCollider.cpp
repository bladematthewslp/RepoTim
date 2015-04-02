#include "NinjaBoxCollider.h"
#include "System.h"
#include "NinjaLogic.h"
#include "PlayerLogic.h"
#include "CStateNinjaStanding.h"
#include "CStateNinjaHitDraggedState.h"

#include <iostream>

NinjaBoxCollider::NinjaBoxCollider(GameObject* gameObject)
	: BoxColliderComponent(gameObject)
{


}

void NinjaBoxCollider::onCollisionEnter(Grid& grid, BoxColliderComponent* other)
{
	if(other->mGameObject->mName == "GridBlock")
	{
		if(dynamic_cast<NinjaLogic*>(mGameObject->mLogicComponent)->isGrounded() == false)
		{
			if(grid.checkCollisionBelow(this) == true)
			{
				mGameObject->move(sf::Vector2f(0, -grid.playerPosition.y ));
				CState* newState = std::unique_ptr<CState>(new CStateNinjaStanding(mGameObject)).release();
				mGameObject->mState = newState;
			}
		}
	}

	if(other->mGameObject->mName == "LongSpikes")
	{
		dynamic_cast<NinjaLogic*>(mGameObject->mLogicComponent)->hit(other->mGameObject, Attacks::LONG_SPIKES);
	}

	
	
}

void NinjaBoxCollider::onCollisionStay(Grid& grid, BoxColliderComponent* other)
{
	if(other->mGameObject->mName == "Player")
	{
		if(dynamic_cast<NinjaLogic*>(mGameObject->mLogicComponent)->isGrounded() == true				// if ninja is grounded
			&& mGameObject->mState->getName() != "CStateNinjaHitDraggedState"							// if ninja is not already being dragged
			&& other->mGameObject->mState->getName() == "AttackState"									// while the player is in attackstate...
			&& other->mGameObject->mRenderComponent->currentAnim == "PLAYER_EXPEL")						// ..and the expel animation is playing
		{
			CState* newState = std::unique_ptr<CState>(new CStateNinjaHitDraggedState(mGameObject)).release();
			mGameObject->mState = newState;
		}
	}
	/*
	bool otherColliderRemoved = BoxColliderComponent::onCollisionStay(grid, other);
	
	if(otherColliderRemoved == true)
		return true;
		*/


	/*
	// resolve collision when ninja falls on top of player
	if(dynamic_cast<PlayerLogic*>(other->mGameObject->mLogicComponent) != nullptr)
	{
		if(dynamic_cast<NinjaLogic*>(mGameObject->mLogicComponent)->getVelocity().y != 0)
		{
			if(mGameObject->getPosition().x < other->mGameObject->getPosition().x)
			{
				dynamic_cast<NinjaLogic*>(mGameObject->mLogicComponent)->move(-10,0);
			}
			else
			{
				dynamic_cast<NinjaLogic*>(mGameObject->mLogicComponent)->move(+10,0);
			}
		}
	}
	*/

	/*
	// resolve collision when ninja collides with player horizonally
	if(other->mGameObject->mName == "Player" || other->mGameObject->mName == "Ninja")
	{
		if(dynamic_cast<NinjaLogic*>(mGameObject->mLogicComponent)->getVelocity().x != 0)
		{
			if(mGameObject->getPosition().x < other->mGameObject->getPosition().x)
			{
				float dist = other->getCollisionBox()->getGlobalBounds().left - (mCollisionBox.getGlobalBounds().left + mCollisionBox.getGlobalBounds().width);
				dynamic_cast<NinjaLogic*>(mGameObject->mLogicComponent)->move(dist,0);
			}
			else if(mGameObject->getPosition().x > other->mGameObject->getPosition().x)
			{
				float dist = (other->getCollisionBox()->getGlobalBounds().left + other->getCollisionBox()->getGlobalBounds().width) - (mCollisionBox.getGlobalBounds().left);
				dynamic_cast<NinjaLogic*>(mGameObject->mLogicComponent)->move(dist,0);
			}
		}
	}
	*/
	
}