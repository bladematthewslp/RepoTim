#include "RunningState.h"
#include "StandingState.h"
#include "FallingState.h"
#include "JumpingState.h"
#include "AttackState.h"
#include "Player.h"
#include "Grid.h"
#include "PlayerLogic.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include <iostream>

RunningState::RunningState(GameObject* player)
	: CState("RunningState")
{
	spriteTimer = 0;
	playSpeed = 5;
	currentFrame = 0;
	numFrames = 8;
}

CState* RunningState::handleInput(GameObject* player, const sf::Event& event)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	if(sf::Keyboard::isKeyPressed(keyDown) == false)
	{
		logic->setVelocityX(0);
		CState* newState = std::unique_ptr<CState>( new StandingState(player) ).release();
		newState->entry(player);
		return newState;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		CState* newState = std::unique_ptr<CState>( new JumpingState(player) ).release();
		newState->entry(player);
		return newState;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		CState* newState = std::unique_ptr<CState>(new AttackState(player)).release();
		newState->entry(player);
		return newState;
	}
	
	return this;
}

CState* RunningState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	player->mRenderComponent->runSpriteAnim(*player);


	logic->move(logic->getVelocity());
	

	switch(logic->getDirection())
	{
		case Direction::Right:
		{
			if(grid.checkCollisionRight(player->mBoxColliderComponent) == true)
			{
				logic->move(-logic->getVelocity().x, 0);
			}
			break;
		}
		case Direction::Left:
		{
			if(grid.checkCollisionLeft(player->mBoxColliderComponent) == true)
			{
				logic->move(-logic->getVelocity().x, 0);
			}
			break;
		}
	}
	if(grid.checkCollisionBelow(player->mBoxColliderComponent) == false   )
	{

		CState* newState = std::unique_ptr<CState>(new FallingState(player)).release();
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