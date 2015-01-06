#include "FallingState.h"

#include "StandingState.h"
#include "PlayerLogic.h"
#include <iostream>

const float MAX_FALLING_SPEED = 5.0f;

FallingState::FallingState(GameObject* player) : gravity(0.0f, 0.3f)
{
	spriteCounter = 0;
	spriteX = 3;
	player->mRenderComponent->setAnimation("Falling");
}

PlayerState* FallingState::handleInput(GameObject* player, Grid& grid, const sf::Event& event)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		logic->setVelocityX(logic->getRunningSpeed());
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		logic->setVelocityX(-logic->getRunningSpeed());
	}
	else 
	{
		logic->setVelocityX(0);
	}
	
	return this;
}


PlayerState* FallingState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);

//	player->mRenderComponent->runSpriteAnim("Falling", *player);
	player->mRenderComponent->runSpriteAnim(*player);
	/*
	spriteCounter++;
	static int spriteSpeed = 5;
	if(spriteCounter % spriteSpeed == 0)
	{
		spriteX++;
		if(spriteX == 6)
			spriteX = 4;
		player->getSprite()->setTextureRect(sf::IntRect(spriteX * 200, 600, 200,200));
	}
	
	*/
	sf::Vector2f oldPosition(player->getPosition() );

	sf::Vector2f newVelocity(logic->getVelocity() + gravity);
	
	if(newVelocity.y > MAX_FALLING_SPEED)
		newVelocity.y = MAX_FALLING_SPEED;
	
	logic->setVelocity(newVelocity);
	logic->move(logic->getVelocity());
	
	
	if(grid.checkCollisionPlayerRight(player) == true)
	{
		sf::Vector2f velocity(logic->getVelocity());
		logic->setVelocityX(-velocity.x);
		logic->move(sf::Vector2f(logic->getVelocity().x, 0));
	}
	else if(grid.checkCollisionPlayerLeft(player) == true)
	{
		sf::Vector2f velocity(logic->getVelocity());
		logic->setVelocityX(-velocity.x);
		logic->move(sf::Vector2f(logic->getVelocity().x, 0));
	}
	
	
	if(grid.checkCollisionUnderPlayer(player) == true   )
	{
		logic->move(sf::Vector2f(0, -grid.playerPosition.y ));

		PlayerState* newState = std::unique_ptr<PlayerState>(new StandingState(player)).release();
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
	logic->setVelocity(playerVelocity);
}