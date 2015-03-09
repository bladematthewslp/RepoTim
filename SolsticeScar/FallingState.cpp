#include "FallingState.h"
#include "AttackStateAir.h"
#include "StandingState.h"
#include "PlayerLogic.h"
#include <iostream>

const float MAX_FALLING_SPEED = 5.0f;

FallingState::FallingState(GameObject* player) 
	: CState("FallingState")
	, gravity(0.0f, 0.3f)
{
	spriteCounter = 0;
	spriteX = 3;
	if(player->mRenderComponent->currentAnim != "PLAYER_SWEEP")
		player->mRenderComponent->setAnimation("Falling");

}

CState* FallingState::handleInput(GameObject* player,  const sf::Event& event)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		logic->setVelocityX(logic->getRunningSpeed());
		logic->updateDirection(Direction::Right);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		logic->setVelocityX(-logic->getRunningSpeed());
		logic->updateDirection(Direction::Left);
	}
	else 
	{
		logic->setVelocityX(0);
	}
	/*
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		CState* newState = std::unique_ptr<CState>(new AttackStateAir(player)).release();
		newState->entry(player);
		return newState;
	}*/
	return this;
}


CState* FallingState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);

	if(player->mRenderComponent->runSpriteAnim(*player) == SpriteAnim::Status::SUCCESS)
	{
		if(player->mRenderComponent->currentAnim == "PLAYER_SWEEP")
			player->mRenderComponent->setAnimation("Falling");
	}

	sf::Vector2f oldPosition(player->getPosition() );

	sf::Vector2f newVelocity(logic->getVelocity() + gravity);
	
	if(newVelocity.y > MAX_FALLING_SPEED)
		newVelocity.y = MAX_FALLING_SPEED;
	
	logic->setVelocity(newVelocity);
	logic->move(logic->getVelocity());
	
	if(grid.checkCollisionRight(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);

	}

	if(grid.checkCollisionLeft(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);
	}
	if(grid.checkCollisionBelow(player->mBoxColliderComponent) == true   )
	{
		logic->move(sf::Vector2f(0, -grid.playerPosition.y ));

		CState* newState = std::unique_ptr<CState>(new StandingState(player)).release();
		newState->entry(player);
		return newState;
	}
	
	
	return this;
}

void FallingState::entry(GameObject* player)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	// increase player's Y velocity
	sf::Vector2f playerVelocity(logic->getVelocity().x, 0);
	//logic->setVelocity(playerVelocity);
}