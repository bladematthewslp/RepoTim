#include "Foreach.hpp"
#include "AttackStateAir.h"
#include "JumpingState.h"
#include "PlayerLogic.h"
#include "FallingState.h"
#include "PlayerInput.h"
#include "SlashBoxLogic.h"
#include "SlashBoxBoxCollider.h"
#include "System.h"
#include <iostream>
#include <array>
#include <queue>

#define CREATE_SLASH_BOX																															\
			GameObjectDesc slashBoxDesc("PlayerAttackBox",sf::RectangleShape(sf::Vector2f(100,130)),	Layer::Player);								\
			GameObject* slashBox = std::unique_ptr<GameObject>(new GameObject(slashBoxDesc)).release();												\
			slashBox->addComponent(ComponentType::LogicComponent, std::unique_ptr<SlashBoxLogic>(new SlashBoxLogic(slashBox)).release());			\
			slashBox->addComponent(ComponentType::BoxColliderComponent, std::unique_ptr<Component>(new SlashBoxBoxCollider(slashBox)).release());	\
			slashBox->mBoxColliderComponent->setVisible(true);																						\
			SlashBoxLogic* slashLogic = dynamic_cast<SlashBoxLogic*>(slashBox->mLogicComponent);													\
			//isAttack = true;																														\
																																					\


//bool isAttack = false;

AttackStateAir::AttackStateAir(GameObject* player)
	: CState("AttackStateAir")
	, timer(0)
	, attackBoxCreated(false)
{
	spriteX = 0;
	slashNumber = 0;
	airJumpSpeed = -1;
	//isAttack = false;
	previousState = player->mState;
}


CState* AttackStateAir::handleInput(GameObject* player, const sf::Event& event)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	
	
	// if the Space key was pressed last frame
	if(event.type == event.KeyPressed)
	{
		
		if(event.key.code == sf::Keyboard::Space)
		{
			//if(player->mRenderComponent->getAnimStatus() == SpriteAnim::SUCCESS)
			if(player->mRenderComponent->isAnimDelayed() == true)
			{
			//	player->mRenderComponent->setAnimation("Slash2Part1");//entry(player);
			}
		}
		/*else if(event.key.code == sf::Keyboard::Up)
		{
			CState* newState = std::unique_ptr<CState>( new JumpingState(player) ).release();
			newState->entry(player);
			return newState;
		}*/
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
	{
		logic->setVelocityX(0);
	}
	return this;
}



CState* AttackStateAir::update(GameObject* player, sf::Time dt, Grid& grid)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	RenderComponent* render = dynamic_cast<RenderComponent*>(player->mRenderComponent);

	int currentFrame = render->mSpriteSet[render->currentAnim]->currentFrame;

	if(currentFrame == 1 && attackBoxCreated == false)
	{
		CREATE_SLASH_BOX;
		slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(225,225));
		slashLogic->init(logic->getDirection(), Attacks::PLAYER_SLASH2, 12);
		slashBox->setPosition(player->getPosition() + sf::Vector2f(-100,-100));
		attackBoxCreated = true;
	}

	if(currentFrame == 2)
		attackBoxCreated = false;
	sf::Vector2f velocity = logic->getVelocity();
	
	if( render->runSpriteAnim(*player) == SpriteAnim::Status::SUCCESS)
	{
		CState* newState = std::unique_ptr<CState>(new FallingState(player)).release();
		newState->entry(player);
		return newState;
	}

	airJumpSpeed += 0.2f;
	logic->setVelocityY(airJumpSpeed);
	logic->move(logic->getVelocity());
	if(grid.checkCollisionBelow(player->mBoxColliderComponent) == true   )
	{
		logic->move(sf::Vector2f(0, -grid.playerPosition.y ));

		CState* newState = std::unique_ptr<CState>(new StandingState(player)).release();
		newState->entry(player);
		return newState;
	}

	return this;
}

void AttackStateAir::entry(GameObject* player)
{
	/*
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	PlayerInput* input = dynamic_cast<PlayerInput*>(player->mInputComponent);
	
	// get move List from logic component
	std::multimap<std::vector<sf::Keyboard::Key>, std::string> list = logic->getMoveList();

	// create key queue to match to move list
	std::vector<sf::Keyboard::Key> keyQueue;
	
	int keyQueueSize = input->getKeyQueue()->size();

	for(int i = 0; i < keyQueueSize; i++)
	{
		keyQueue.push_back(input->getKeyQueue()->front());
		input->getKeyQueue()->pop();
	}
	
	// check if pressed keys matches an action in the move list
	for(std::multimap<std::vector<sf::Keyboard::Key>, std::string>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		// if so...
		if(keyQueue == iter->first && Attacks::getAttack(iter->second).mIsAirAttack == true)
		{
			std::cout << iter->second << std::endl;
			player->mRenderComponent->setAnimation(iter->second);
		}
	}

	// if keys did not match any move list, set default slash animation
	player->mRenderComponent->setAnimation("PLAYER_SWEEP");

	*/


}