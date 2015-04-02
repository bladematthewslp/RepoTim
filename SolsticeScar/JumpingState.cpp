#include "JumpingSpriteHelper.inl"
#include "JumpingState.h"
#include "FallingState.h"
#include "AttackStateAir.h"
#include  "PlayerLogic.h"
#include "PlayerInput.h"
#include "Player.h"
#include "BoxColliderComponent.h"
#include <iostream>
#include <vector>
const float MAX_JUMPING_SPEED = 5.0f;



JumpingState::JumpingState(GameObject* player) 
	: CState("JumpingState")
	, gravity(0.0f, 0.5f)
	, oldPosition()
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	System::mSoundPlayer.play(SoundEffect::Jump);
	spriteX = 1;
	spriteCounter = 0;
	player->mRenderComponent->setAnimation("Jumping");
	dynamic_cast<PlayerInput*>(player->mInputComponent)->clearKeyQueue();
	//std::cout << "NEW JUMPING STATE" << std::endl;

}

CState* JumpingState::handleInput(GameObject* player, const sf::Event& event)
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
	}
	*/
	return this;
}


CState* JumpingState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	//std::cout << "JUMPING STATE UPDATE" << std::endl;
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
	

	if(grid.checkCollisionRight(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);

	}

	if(grid.checkCollisionLeft(player->mBoxColliderComponent) == true)
	{
		logic->move(-logic->getVelocity().x, 0);
	}

	if(grid.checkCollisionAbove(player->mBoxColliderComponent) == true)
	{
		logic->setVelocityY(-newVelocity.y);
		logic->move(0, logic->getVelocity().y);
	}	
	
	/*
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
	}*/
	
	
	
	if(logic->getVelocity().y > 0)
	{
		CState* newState = std::unique_ptr<CState>(new FallingState(player)).release();
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

