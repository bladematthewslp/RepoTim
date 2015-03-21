#include "Foreach.hpp"
#include "AttackStateAir.h"
#include "JumpingState.h"
#include "PlayerLogic.h"
#include "FallingState.h"
#include "PlayerInput.h"
#include "SlashBoxLogic.h"
#include "SlashBoxBoxCollider.h"
#include "AttackState.h"
#include "System.h"
#include <iostream>
#include <array>
#include <queue>

#define CREATE_SLASH_BOX																															\
			GameObjectDesc slashBoxDesc("PlayerAttackBox",sf::RectangleShape(sf::Vector2f(100,130)),	Layer::Player);								\
			slashBox = std::unique_ptr<GameObject>(new GameObject(slashBoxDesc)).release();												\
			slashBox->addComponent(ComponentType::LogicComponent, std::unique_ptr<SlashBoxLogic>(new SlashBoxLogic(slashBox)).release());			\
			slashBox->addComponent(ComponentType::BoxColliderComponent, std::unique_ptr<Component>(new SlashBoxBoxCollider(slashBox)).release());	\
			slashBox->mBoxColliderComponent->setVisible(false);																						\
			SlashBoxLogic* slashLogic = dynamic_cast<SlashBoxLogic*>(slashBox->mLogicComponent);													\
			//isAttack = true;																														\
																																					\


//bool isAttack = false;

AttackStateAir::AttackStateAir(GameObject* player)
	: CState("AttackStateAir")
	, timer(0)
	, attackBoxCreated(false)
	, slashBox(nullptr)
{
	spriteX = 0;
	slashNumber = 0;
	airJumpSpeed = -1;
	//isAttack = false;
	//previousState = player->mState;

	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	soundEffectPlayed = false;
	
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

	// handle sounds
	if(soundEffectPlayed == false)
	{
		if(render->currentAnim == "PLAYER_SWEEP")
		{
			playSound(SoundEffect::DojiSwordSwingAir, logic);
		}
		
	}

	// handle downward velocity
	if(render->currentAnim == "PLAYER_HAILBRINGER")
	{
		float y = logic->getVelocity().y;
		logic->setVelocityY(8);
		logic->move(logic->getVelocity() );
	}


	
	// handle slash box
	if(attackBoxCreated == false)
	{
		if(render->currentAnim == "PLAYER_HAILBRINGER")
		{
			if(currentFrame == 2)
			{
				CREATE_SLASH_BOX;
				slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(110,70));
				slashLogic->init(logic->getDirection(), Attacks::PLAYER_HAILBRINGER, -1);
				//if(logic->getDirection() == Direction::Right)
				//	slashBox->setPosition(sf::Vector2f(-10,-40));
				//else if(logic->getDirection() == Direction::Left)
				//	slashBox->setPosition(sf::Vector2f(-100,-40));
				player->addChild(slashBox);
				attackBoxCreated = true;
			}
		}
		else if(render->currentAnim == "PLAYER_SWEEP")
		{
			if(currentFrame == 2)
			{
				CREATE_SLASH_BOX;
				slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(110,105));
				slashLogic->init(logic->getDirection(), Attacks::PLAYER_SLASH2, 12);
				if(logic->getDirection() == Direction::Right)
					slashBox->setPosition(player->getPosition() + sf::Vector2f(0,-40));
				else if(logic->getDirection() == Direction::Left)
					slashBox->setPosition(player->getPosition() + sf::Vector2f(-100,-40));
				attackBoxCreated = true;
			}

			if(currentFrame == 3)
			{
				attackBoxCreated = false;
				CREATE_SLASH_BOX;
				slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(105,110));
				slashLogic->init(logic->getDirection(), Attacks::PLAYER_SLASH2, 12);
				if(logic->getDirection() == Direction::Right)
					slashBox->setPosition(player->getPosition() + sf::Vector2f(0,0));
				else if(logic->getDirection() == Direction::Left)
					slashBox->setPosition(player->getPosition() + sf::Vector2f(-100,0));
			}
		}
	}
	

	sf::Vector2f velocity = logic->getVelocity();
	
	if( render->runSpriteAnim(*player) == SpriteAnim::Status::SUCCESS)
	{
		if(render->currentAnim == "PLAYER_HAILBRINGER")
		{
			soundEffectPlayed = false;
		}
		else if(render->currentAnim == "PLAYER_HAILBRINGER_PART2")
		{
			CState* newState = std::unique_ptr<CState>(new StandingState(player)).release();
			newState->entry(player);
			return newState;
		}
		else
		{
			CState* newState = std::unique_ptr<CState>(new FallingState(player)).release();
			newState->entry(player);
			return newState;
		}
	}

	airJumpSpeed += 0.2f;
	logic->setVelocityY(airJumpSpeed);
	logic->move(logic->getVelocity());
	if(grid.checkCollisionBelow(player->mBoxColliderComponent) == true   )
	{
		
		logic->move(sf::Vector2f(0, -grid.playerPosition.y ));
		if(render->currentAnim == "PLAYER_HAILBRINGER")
		{
			CState* newState = std::unique_ptr<CState>(new AttackState(player)).release();
			render->setAnimation("PLAYER_HAILBRINGER_PART2");
			System::removeGameObject(slashBox);
			logic->setVelocityY(0);
			newState->entry(player);
			return newState;

			
			
		}

		else if(render->currentAnim != "PLAYER_HAILBRINGER_PART2")
		{
			CState* newState = std::unique_ptr<CState>(new StandingState(player)).release();
			newState->entry(player);
			return newState;
		}
	}

	return this;
}

void AttackStateAir::playSound(SoundEffect::ID effect, PlayerLogic* playerLogic)
{
	playerLogic->mSoundPlayer.play(effect);
	soundEffectPlayed = true;

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