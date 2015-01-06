#include "RunningState.h"
#include "StandingState.h"
#include "FallingState.h"
#include "JumpingState.h"
#include "Player.h"
#include "Grid.h"
#include "PlayerLogic.h"
#include "GameObject.h"
#include <iostream>

RunningState::RunningState(GameObject* player)
{
	spriteTimer = 0;
	playSpeed = 5;
	currentFrame = 0;
	numFrames = 8;
}

PlayerState* RunningState::handleInput(GameObject* player, Grid& grid, const sf::Event& event)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	if(sf::Keyboard::isKeyPressed(keyDown) == false)
	{
		logic->setVelocityX(0);
		PlayerState* newState = std::unique_ptr<PlayerState>( new StandingState(player) ).release();
		newState->entry(player);
		return newState;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		PlayerState* newState = std::unique_ptr<PlayerState>( new JumpingState(player) ).release();
		newState->entry(player);
		return newState;
	}
	
	return this;
}

PlayerState* RunningState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	//player->mRenderComponent->runSpriteAnim("Running", *player);
	player->mRenderComponent->runSpriteAnim(*player);
	/*
	sf::RectangleShape* sprite = player->getSprite();
	spriteTimer++;
	
	if(spriteTimer % playSpeed == 0)
	{
		currentFrame++;
		if(currentFrame == numFrames)
			currentFrame = 0;
		sprite->setTextureRect(sf::IntRect(currentFrame * 200, 200, 200,200));
	}
	*/

	logic->move(logic->getVelocity());
	//logic->updateBox();
	//std::cout << logic->box.top << std::endl;
	//std::cout << player->getPosition().y << std::endl;
	
	
	switch(logic->getDirection())
	{
		case Direction::Right:
		{
			if(grid.checkCollisionPlayerRight(player) == true)
			{
				logic->move(-logic->getVelocity().x, 0);
			}
			break;
		}
		case Direction::Left:
		{
			if(grid.checkCollisionPlayerLeft(player) == true)
			{
				logic->move(-logic->getVelocity().x, 0);
			}
			break;
		}
	}
	
	if(grid.checkWalkingOnTile(player) == false)		// if returns false, player is not walking on tile
	{
		PlayerState* newState = std::unique_ptr<PlayerState>( new FallingState(player) ).release();
		newState->entry(player);
		return newState;
	}
	
	

	return this;
}



void RunningState::entry(GameObject* player)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);

	player->mRenderComponent->setAnimation("Running");


	// set the player velocity
	sf::Vector2f velocity(logic->getVelocity());
	velocity.x = logic->getRunningSpeed();
	logic->setVelocity(velocity);

	//player->getSprite()->setTextureRect(sf::IntRect(currentFrame * 200, 200, 200,200));

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		isRightKeyDown = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		isLeftKeyDown = true;
	}
}

void RunningState::setKeyDownParams(GameObject* player, sf::Keyboard::Key key)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	keyDown = key;
	switch(keyDown)
	{
		case sf::Keyboard::Right:
			logic->setVelocityX(logic->getRunningSpeed());
			break;
		case sf::Keyboard::Left:
			logic->setVelocityX(-logic->getRunningSpeed());
			break;
	}
}