#include "CStateNinjaHitDraggedState.h"
#include "CStateNinjaStanding.h"
#include "CStateNinjaFalling.h"
#include "PlayerLogic.h"
#include "NinjaLogic.h"

CStateNinjaHitDraggedState::CStateNinjaHitDraggedState(GameObject* character)
	: CState("CStateNinjaHitDraggedState")
{
	NinjaLogic* ninjaLogic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	PlayerLogic* playerLogic = dynamic_cast<PlayerLogic*>(ninjaLogic->player->mLogicComponent);

	int playerPosX = ninjaLogic->player->getPosition().x;
	int ninjaPosX = character->getPosition().x;
	
	if(playerPosX >= ninjaPosX)
	{
		ninjaLogic->setDirection(Direction::Right);
		character->setPosition(playerPosX - 50, character->getPosition().y);
	}
	else
	{
		ninjaLogic->setDirection(Direction::Left);
		character->setPosition(playerPosX + 50, character->getPosition().y);
	}

	character->mRenderComponent->setAnimation("DraggedByExpel");
	character->mRenderComponent->runSpriteAnim(*character);
}

void		CStateNinjaHitDraggedState::entry(GameObject* character)
{

}

CState*		CStateNinjaHitDraggedState::handleInput(GameObject* character, const sf::Event& event)
{

	return this;

}


CState*		CStateNinjaHitDraggedState::update(GameObject* character, sf::Time dt, Grid& grid)
{
	NinjaLogic* ninjaLogic = dynamic_cast<NinjaLogic*>(character->mLogicComponent);
	PlayerLogic* playerLogic = dynamic_cast<PlayerLogic*>(ninjaLogic->player->mLogicComponent);

	if(player->mState->getName() == "AttackState" && player->mRenderComponent->currentAnim == "PLAYER_EXPEL" && ninjaLogic->isGrounded() == true )
	{
		int playerPosX = ninjaLogic->player->getPosition().x;
		int ninjaPosX = character->getPosition().x;
		//int playerPosX = ninjaLogic->player->getPosition().x;
		//int ninjaPosX = character->getPosition().x;
	
		if(playerPosX >= ninjaPosX)
		{
			ninjaLogic->setDirection(Direction::Right);
			ninjaLogic->setVelocityX(-10);
			//character->setPosition(playerPosX - 50, character->getPosition().y);
		}
		else
		{
			ninjaLogic->setDirection(Direction::Left);
			//character->setPosition(playerPosX + 50, character->getPosition().y);
			ninjaLogic->setVelocityX(10);
		}
		/*
		if(playerPosX >= ninjaPosX)
		{
			// change directions if necessary
			if(ninjaLogic->getDirection() == playerLogic->getDirection() )  // if ninja and player face same direction...
			{
				ninjaLogic->setVelocityX(-ninjaLogic->getDirection() * 10);
			}
		}
		else
		{
			// change directions if necessary
			if(ninjaLogic->getDirection() == playerLogic->getDirection() )  // if ninja and player face same direction...
			{
				ninjaLogic->setVelocityX(-ninjaLogic->getDirection() * 10);
			}
		}
		*/
		if(playerPosX > ninjaPosX)
		{
		}
		//else
			//ninjaLogic->setVelocityX(ninjaLogic->getDirection() * 10);

		//ninjaLogic->setVelocityX(-ninjaLogic->getDirection() * 10);

		ninjaLogic->move(ninjaLogic->getVelocity().x, 0);
		switch(ninjaLogic->getDirection())
		{
			case Direction::Right:
			{
				if(grid.checkCollisionLeft(character->mBoxColliderComponent) == true)
				{
					ninjaLogic->move(-ninjaLogic->getVelocity().x, 0);
				}
				break;
			}
			case Direction::Left:
			{
				if(grid.checkCollisionRight(character->mBoxColliderComponent) == true)
				{
					ninjaLogic->move(-ninjaLogic->getVelocity().x, 0);
				}
				break;
			}
		}
	}
	else if( ninjaLogic->isGrounded() == false)
	{
		CState* newState = std::unique_ptr<CState>(new CStateNinjaFalling(character)).release();
		newState->entry(character);
		return newState;
	}
	else
	{
		CState* newState = std::unique_ptr<CState>(new CStateNinjaStanding(character)).release();
		newState->entry(character);
		return newState;
	}
	return this;

}