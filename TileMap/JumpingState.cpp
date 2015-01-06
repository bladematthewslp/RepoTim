#include "JumpingSpriteHelper.inl"
#include "JumpingState.h"
#include "FallingState.h"
#include  "PlayerLogic.h"
#include "Player.h"
#include <iostream>
#include <vector>
const float MAX_JUMPING_SPEED = 5.0f;



JumpingState::JumpingState(GameObject* player) : gravity(0.0f, 0.3f), oldPosition()
{
	spriteX = 1;
	spriteCounter = 0;
	player->mRenderComponent->setAnimation("Jumping");

}

PlayerState* JumpingState::handleInput(GameObject* player, Grid& grid, const sf::Event& event)
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


PlayerState* JumpingState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	//player->mRenderComponent->runSpriteAnim("Jumping", *player);
	player->mRenderComponent->runSpriteAnim(*player);
	/*
	spriteCounter++;
	
	switch(spriteCounter)
	{
		case 5:
		case 15:
			spriteX++;
			player->getSprite()->setTextureRect(sf::IntRect(spriteX * 200, 600, 200,200));
			break;


	}
	*/
	// Get player's current velocity with applied gravity and store it. If new velocity exceeds MAX_FALLING_SPEED, cap the fall velocity
	sf::Vector2f newVelocity(logic->getVelocity() + gravity);
	
	if(newVelocity.y > MAX_JUMPING_SPEED)
		newVelocity.y = MAX_JUMPING_SPEED;
	
	logic->setVelocity(newVelocity);
	logic->move(logic->getVelocity());
	
	if(grid.checkCollisionPlayerRight(player) == true)
	{
		logic->move(-logic->getVelocity().x, 0);

	}else 
	if(grid.checkCollisionPlayerLeft(player) == true)
	{
		logic->move(-logic->getVelocity().x, 0);
	}
	
	if(grid.checkCollisionAbovePlayer(player) == true)
	{
		logic->setVelocityY(-newVelocity.y);
		logic->move(logic->getVelocity());
	}
	
	
	
	if(logic->getVelocity().y > 0)
	{
		PlayerState* newState = std::unique_ptr<PlayerState>(new FallingState(player)).release();
		newState->entry(player);
		return newState;
	}

	return this;
}

void JumpingState::entry(GameObject* player)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	player->getSprite()->setTextureRect(sf::IntRect(spriteX * 200, 600, 200,200));
	
	// increase player's Y velocity
	sf::Vector2f playerVelocity(logic->getVelocity().x, -13);
	logic->setVelocity(playerVelocity);
}

void JumpingState::accelerate()
{
	
}

