#include "SlashBoxBoxCollider.h"
#include "NinjaLogic.h"
#include "PlayerLogic.h"
#include "RyobeLogic.h"
#include "SlashBoxLogic.h"
#include "AttackType.h"
#include "DazedState.h"
#include "AttackBlockedState.h"
#include "AttackBlockedAirState.h"
#include "System.h"

SlashBoxBoxCollider::SlashBoxBoxCollider(GameObject* gameObject)
	: BoxColliderComponent(gameObject)
{
	//this->setVisible(true);
	this->mCollisionBox.setSize(sf::Vector2f(120,120));
	//std::cout << "NEW BOX " << std::endl;
}

void SlashBoxBoxCollider::onCollisionEnter(Grid& grid, BoxColliderComponent* other)
{
	SlashBoxLogic* logic = dynamic_cast<SlashBoxLogic*>(mGameObject->mLogicComponent);
	PlayerLogic* playerLogic = dynamic_cast<PlayerLogic*>(logic->getPlayer()->mLogicComponent);
	/*if(other->mGameObject->mName == "Ninja")
	{
		dynamic_cast<NinjaLogic*>(other->mGameObject->mLogicComponent)->hit(other->mGameObject, logic->getAttack());
		System::removeGameObject(mGameObject);
	}*/

	
	if(other->mGameObject->mLayerName == Layer::Enemy)
	{
		if(other->mGameObject->mName == "Ninja")
		{
			dynamic_cast<NinjaLogic*>(other->mGameObject->mLogicComponent)->hit(other->mGameObject, logic->getAttack());
			
		}
		if(other->mGameObject->mName == "Ryobe")
		{
			RyobeLogic* ryobeLogic = dynamic_cast<RyobeLogic*>(other->mGameObject->mLogicComponent);
			// if ryobe is untouchable when he is hit
			if(ryobeLogic->isUntouchable() == true)
			{
				// set player state, depending on if he is grounded or airborne
				if(playerLogic->isGrounded() == true)
					playerLogic->setNewState(new AttackBlockedState(logic->getPlayer()));
				else
					playerLogic->setNewState(new AttackBlockedAirState(logic->getPlayer()));
			}
			else
				ryobeLogic->hit(other->mGameObject, logic->getAttack());
		}
		else if(other->mGameObject->mName == "Dagger")
		{
			System::removeGameObject(other->mGameObject);
		}

		if(logic->getAttack() != Attacks::PLAYER_CHOPPERSTYLE)
		System::removeGameObject(mGameObject);
	}
	
}