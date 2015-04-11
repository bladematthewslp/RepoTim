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
	
	int playerPosX = playerLogic->mGameObject->getPosition().x;
	int ninjaPosX = character->getPosition().x;
	
	float playerVelX = playerLogic->getVelocity().x;
	//std::cout << playerVelX << std::endl;
	
	if(playerPosX >= ninjaPosX)
	{
		if(playerVelX > 0)					// if player is moving right
		{
			ninjaLogic->setDirection(Direction::Left);
			character->setPosition(playerPosX + 50, character->getPosition().y);
		}
		else if(playerVelX < 0)				// if player is moving left
		{
			ninjaLogic->setDirection(Direction::Right);
			character->setPosition(playerPosX - 50, character->getPosition().y);
		}
	}
	else
	{
		if(playerVelX < 0)				// if player is moving left
		{
			ninjaLogic->setDirection(Direction::Right);
			character->setPosition(playerPosX - 50, character->getPosition().y);
		}
		else if(playerVelX > 0)					// if player is moving right
		{
			ninjaLogic->setDirection(Direction::Left);
			character->setPosition(playerPosX + 50, character->getPosition().y);
		}

		
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
		int playerPosX = playerLogic->mGameObject->getPosition().x;
		int ninjaPosX = character->getPosition().x;
		//int playerPosX = ninjaLogic->player->getPosition().x;
		//int ninjaPosX = character->getPosition().x;
		float playerVelX = playerLogic->getVelocity().x;
		//std::cout << playerVelX << std::endl;
	
		if(playerPosX >= ninjaPosX)
		{
			if(playerVelX > 0)					// if player is moving right
			{
				//ninjaLogic->setDirection(Direction::Left);
				//character->setPosition(playerPosX + 50, character->getPosition().y);
				ninjaLogic->setVelocityX(10);
			}
			else if(playerVelX < 0)				// if player is moving left
			{
				//ninjaLogic->setDirection(Direction::Right);
				//character->setPosition(playerPosX - 50, character->getPosition().y);
				ninjaLogic->setVelocityX(-10);
			}
		}
		else
		{
			if(playerVelX < 0)				// if player is moving left
			{
				//ninjaLogic->setDirection(Direction::Right);
				//character->setPosition(playerPosX - 50, character->getPosition().y);
				ninjaLogic->setVelocityX(-10);
			}
			else if(playerVelX > 0)					// if player is moving right
			{
				//ninjaLogic->setDirection(Direction::Left);
				//character->setPosition(playerPosX + 50, character->getPosition().y);
				ninjaLogic->setVelocityX(10);
			}

		
		}
		/*
		sf::Vector2f playerVelocity = playerLogic->getVelocity();
		if(playerPosX >= ninjaPosX)
		{
			ninjaLogic->setDirection(Direction::Right);
			ninjaLogic->setVelocityX(playerVelocity.x);
			character->setPosition(playerPosX + 50, character->getPosition().y);
		}
		else
		{
			ninjaLogic->setDirection(Direction::Left);
			character->setPosition(playerPosX - 50, character->getPosition().y);
			ninjaLogic->setVelocityX(playerVelocity.x);
		}
		*/


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