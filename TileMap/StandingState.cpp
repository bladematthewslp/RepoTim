#include "StandingState.h"
#include "JumpingState.h"
#include "GuardState.h"
#include "AttackState.h"
#include "AttackBlockedState.h"
#include "FallingState.h"
#include "RunningState.h"
#include "DazedState.h"
//#include "Player.h"
#include "PlayerLogic.h"
#include "HitState.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include <iostream>
#include <array>

StandingState::StandingState(GameObject* player)
	: CState("StandingState")
{
	//player->getSprite()->setTextureRect(sf::IntRect(0,0,200,200));
	//player->mRenderComponent->runSpriteAnim("Standing", *player);
	player->mRenderComponent->setAnimation("Standing");
}

CState* StandingState::handleInput(GameObject* player, const sf::Event& event)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//std::cout << "!!!!" << std::endl;
		RunningState* newState = std::unique_ptr<RunningState>( new RunningState(player) ).release();
		logic->updateDirection(Direction::Right);
		newState->entry(player);
		newState->setKeyDownParams(player, sf::Keyboard::Right);
		//player->setVelocityX(player->getRunningSpeed());
		return newState;
		
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		RunningState* newState = std::unique_ptr<RunningState>( new RunningState(player) ).release();
		
		logic->updateDirection(Direction::Left);
		newState->entry(player);
		newState->setKeyDownParams(player, sf::Keyboard::Left);
		//player->setVelocityX(-player->getRunningSpeed());
		return newState;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		CState* newState = std::unique_ptr<CState>( new JumpingState(player) ).release();
		newState->entry(player);
		return newState;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		CState* newState = std::unique_ptr<CState>(new GuardState(player)).release();
		newState->entry(player);
		return newState;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//CState* newState = std::unique_ptr<CState>(new AttackState(player)).release();
		//newState->entry(player);
		//return newState;
	}


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		CState* newState = std::unique_ptr<CState>(new AttackBlockedState(player)).release();
		return newState;
	}
	return this;
}

CState* StandingState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	player->mRenderComponent->runSpriteAnim(*player);//setAnimation("Standing");//runSpriteAnim("Standing", *player);
	
	if(grid.checkWalkingOnTile(player) == false)		// if returns false, player is not walking on tile
	{
		CState* newState = std::unique_ptr<CState>( new FallingState(player) ).release();
		newState->entry(player);
		return newState;
	}
	
	return this;
}

void snaptoGrid(Component* player)
{
	/*float i = 0;
	float spriteBottomY = player->getPosition().y + (player->getSprite().getGlobalBounds().height/2);
	while( i < spriteBottomY)
	{
		i += 32;
	}
	float diff = i - spriteBottomY;
	
	player->getSprite().move(0,diff);*/
}

void StandingState::entry(GameObject* player)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	logic->setGrounded(true);

	std::cout << "entry" << std::endl;
	logic->setVelocity(sf::Vector2f(0,0));

	

	//player->getSprite().setTextureRect(sf::IntRect(0,0, 200,200));
	
	//player->slashNumber = -1;
}

