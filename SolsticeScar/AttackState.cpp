#include "Foreach.hpp"
#include "AttackState.h"
#include "JumpingState.h"
#include "PlayerLogic.h"
#include "PlayerInput.h"
#include "SlashBoxLogic.h"
#include "SlashBoxBoxCollider.h"
#include "System.h"
#include "SoundEffectLogic.h"
//#include "GameObjectManager.h"
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
			isAttack = true;																														\
																																					\


bool isAttack = false;

AttackState::AttackState(GameObject* player)
	: CState("AttackState")
	, timer(0)
	, mGameObject(*player)
{
	timeInState = 0;
	delayTimer = 0;
	spriteX = 0;
	slashNumber = 0;
	//player->mRenderComponent->setAnimation("Slash1");
	isAttack = false;
	std::cout << "NEW ATTACK STATE" << std::endl;
	soundEffectPlayed = false;
	
}

GameObject* AttackState::createSlashBox()
{
	GameObjectDesc slashBoxDesc("AttackBox",sf::RectangleShape(sf::Vector2f(100,130)),	Layer::Player);
	GameObject* slashBox = std::unique_ptr<GameObject>(new GameObject(slashBoxDesc)).release();
	slashBox->addComponent(ComponentType::LogicComponent, std::unique_ptr<SlashBoxLogic>(new SlashBoxLogic(slashBox)).release());
	slashBox->addComponent(ComponentType::BoxColliderComponent, std::unique_ptr<Component>(new SlashBoxBoxCollider(slashBox)).release());	
	slashBox->mBoxColliderComponent->setVisible(true);
	SlashBoxLogic* slashLogic = dynamic_cast<SlashBoxLogic*>(slashBox->mLogicComponent);
	isAttack = true;
	return slashBox;
}

void AttackState::setAttack(Attacks::Name attackName)
{

	if(attackName == Attacks::PLAYER_SLASH)
	{
		switch(slashNumber)
		{
		case 0:
			mGameObject.mRenderComponent->setAnimation("Slash1");
			break;
		case 1:
			mGameObject.mRenderComponent->setAnimation("Slash2Part1");
			break;
		default:
			mGameObject.mRenderComponent->setAnimation("Slash3");
			break;
		}
		slashNumber++;
	}
	else
	{
		mGameObject.mRenderComponent->setAnimation(attackName);
	}
}

CState* AttackState::handleInput(GameObject* player, const sf::Event& event)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	// allow player to switch directions in the beginning of the attack state
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)  && timeInState <= 6)
	{
		logic->updateDirection(Direction::Right);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  && timeInState <= 6)
	{
		logic->updateDirection(Direction::Left);
	}
	
	// if the Space key was pressed last frame
	if(event.type == event.KeyPressed)
	{
		RenderComponent* render = dynamic_cast<RenderComponent*>(player->mRenderComponent);
		if(event.key.code == sf::Keyboard::Space)
		{
			if(player->mRenderComponent->isAnimDelayed() == true)
			{
				//entry(player);
			}
		}
		else if(event.key.code == sf::Keyboard::Up)
		{
			CState* newState = std::unique_ptr<CState>( new JumpingState(player) ).release();
			newState->entry(player);
			return newState;
		}
		
	}
	
	return this;
}



CState* AttackState::update(GameObject* player, sf::Time dt, Grid& grid)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	RenderComponent* render = dynamic_cast<RenderComponent*>(player->mRenderComponent);

	

	// play sound effect
	if(soundEffectPlayed == false)
	{
		

		if(render->currentAnim == "Slash1")
			playSound(SoundEffect::DojiSwordSwing1, logic);
		else if(render->currentAnim == "Slash2Part1")
			playSound(SoundEffect::DojiSwordSwing2, logic);
		else if(render->currentAnim == "QuickStinger" || render->currentAnim == "QuickUprising")
			playSound(SoundEffect::DojiSwordSwingQuick, logic);
		else if(render->currentAnim == "Slash3")
			playSound(SoundEffect::DojiSwordSwing3, logic);
		else if(render->currentAnim == "PLAYER_IMPACT" && render->mSpriteSet[render->currentAnim]->currentFrame == 3)
			playSound(SoundEffect::DojiImpact, logic);
		else if(render->currentAnim == "PLAYER_CHOPPERSTYLE")
		{
			playSound(SoundEffect::DojiChopperStyle, logic);
			
			
			/*GameObjectDesc soundDesc("Multislash");
			GameObject* sound = std::unique_ptr<GameObject>(new GameObject(soundDesc)).release();
			sound->addComponent(std::unique_ptr<Component>(new SoundEffectLogic(player)).release());
			dynamic_cast<SoundEffectLogic*>(sound->mLogicComponent)->mSoundPlayer.play(SoundEffect::DojiChopperStyle);
			soundEffectPlayed = true;

			*/
		}
		else if(render->currentAnim == "PLAYER_HAILBRINGER_PART2")
		{
			playSound(SoundEffect::DojiHailBringerLanding, logic);
		}

	}

	int currentFrame = render->mSpriteSet[render->currentAnim]->currentFrame;
	
	delayTimer++;
	timeInState++;
	if(currentFrame == 2 && isAttack == false)
	{

	}

	// create slash boxes for regular slashes
	if(currentFrame == 2 && isAttack == false)
	{
		
		
		if(render->currentAnim == "Slash1")
		{
			CREATE_SLASH_BOX;
			
			slashLogic->init(logic->getDirection(), Attacks::PLAYER_SLASH1, 15);
			slashLogic->setAttackType(Attacks::PLAYER_SLASH1);
			isAttack = true;
		}
		else if(render->currentAnim == "Slash2Part1")
		{
			CREATE_SLASH_BOX;
			slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(90,60));
			slashLogic->init(logic->getDirection(), Attacks::PLAYER_SLASH2, 12);
			isAttack = true;
		}
		else if(render->currentAnim == "Slash3")
		{
			CREATE_SLASH_BOX;
			slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(230,190));
			slashLogic->init(logic->getDirection(), Attacks::PLAYER_SLASH3, 12);
			isAttack = true;
		}
	}
	else if(currentFrame == 5 && isAttack == false)
	{
		if(render->currentAnim == Attacks::PLAYER_IMPACT)
		{
				
			CREATE_SLASH_BOX;
			slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(170,110));
			slashLogic->init(logic->getDirection(), Attacks::PLAYER_IMPACT, 12);
		}
	}
	else if(currentFrame == 6 && isAttack == false)
	{
		if(render->currentAnim == Attacks::PLAYER_CHOPPERSTYLE)
		{
			CREATE_SLASH_BOX;
			slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(215,150));
			slashLogic->init(logic->getDirection(), Attacks::PLAYER_CHOPPERSTYLE, 70);
			isAttack = true;
		}
	}
	else if(render->currentAnim == "QuickUprising")
	{
		if(currentFrame == 3 && isAttack == false)
		{
			CREATE_SLASH_BOX;
			slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(115,200));
			slashLogic->init(logic->getDirection(), Attacks::PLAYER_QUICKUPRISING, 11);
			isAttack = true;
			//std::cout << "BOX!" << std::endl;
		}
		if(currentFrame > 3)
			isAttack = false;
		
	}
	else if(render->currentAnim == "QuickStinger")
	{
		if(currentFrame == 3 && isAttack == false)
		{
			CREATE_SLASH_BOX;
			slashBox->mBoxColliderComponent->getCollisionBox()->setSize(sf::Vector2f(115,130));
			slashLogic->init(logic->getDirection(), Attacks::PLAYER_QUICKSTINGER, 11);
			isAttack = true;
			//std::cout << "BOX!" << std::endl;
		}
		if(currentFrame > 3)
			isAttack = false;
		
	}
	
	//if(currentFrame == 3 || currentFrame == 7 )
		//isAttack = false;
	if(player->mRenderComponent->currentAnim == "QuickUprising")// && render->isAnimDelayed() == true)
	{
		
	}
	
	if( player->mRenderComponent->runSpriteAnim(*player) == SpriteAnim::SUCCESS )
	{
		
		if(logic->isGrounded() == true)
		{
			if(player->mRenderComponent->currentAnim == "PLAYER_IMPACT")
				player->mRenderComponent->setAnimation("PLAYER_IMPACT_REPEATED");
			else if(player->mRenderComponent->currentAnim == "PLAYER_IMPACT_REPEATED")
			{
				timer++;
				if(timer == 2)
				{
					player->mRenderComponent->setAnimation("PLAYER_IMPACT_RECOVERING");
				}
			}
			else if(player->mRenderComponent->currentAnim == "PLAYER_IMPACT_RECOVERING")
			{
				CState* newState = std::unique_ptr<CState>(new StandingState(player)).release();
				newState->entry(player);
				return newState;
			}
			else if(player->mRenderComponent->currentAnim == "PLAYER_CHOPPERSTYLE")
			{
				player->mRenderComponent->setAnimation("PLAYER_CHOPPERSTYLE_REPEATED");
			}
			else if(player->mRenderComponent->currentAnim == "PLAYER_CHOPPERSTYLE_REPEATED")
			{
				timer++;
				if(timer == 6)
				{
					player->mRenderComponent->setAnimation("PLAYER_CHOPPERSTYLE_RECOVERING");
				}
			}
			else if(player->mRenderComponent->currentAnim == "Slash2Part1")
			{
				timer++;
				//std::cout << timer << std::endl;
				if(timer == 5)
				{
					player->mRenderComponent->setAnimation("Slash2Part2");
				}
			}
			else if(player->mRenderComponent->currentAnim == "QuickUprising")
			{
				timer++;
				if(timer == 10)
				{
					// ...return to Standing state
					CState* newState = std::unique_ptr<CState>(new StandingState(player)).release();
					newState->entry(player);
					return newState;
				}
			}
			else if(player->mRenderComponent->currentAnim == "QuickStinger")
			{
				timer++;
				//std::cout << "DELAYED" << std::endl;
				if(timer == 10)
				{
					// ...return to Standing state
					CState* newState = std::unique_ptr<CState>(new StandingState(player)).release();
					newState->entry(player);
					return newState;
				}
			}
			else
			{
				// ...return to Standing state
				CState* newState = std::unique_ptr<CState>(new StandingState(player)).release();
				newState->entry(player);
				return newState;
			}
		}
	}
	

	return this;
}

void AttackState::playSound(SoundEffect::ID effect, PlayerLogic* playerLogic)
{
	playerLogic->mSoundPlayer.play(effect);
	soundEffectPlayed = true;

}

void AttackState::entry(GameObject* player)
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
	

	//bool matchFound = false;
	// check if pressed keys matches an action in the move list
	for(std::multimap<std::vector<sf::Keyboard::Key>, std::string>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		// if so...
		if(keyQueue == iter->first 
			&& Attacks::getAttack(iter->second).mIsAirAttack == false
			&& iter->second != Attacks::PLAYER_SLASH)
		{
			
			//player->mRenderComponent->setAnimation(iter->second);//"Slash1");	std::cout << "Match!" << std::endl;
			return;
		}
	}
	*/
	// if keys did not match any move list, set default slash animation accordingly
	/*
	switch(slashNumber)
	{
		case 0:
			player->mRenderComponent->setAnimation("Slash1");
			break;
		case 1:
			player->mRenderComponent->setAnimation("Slash2Part1");
			break;
		default:
			player->mRenderComponent->setAnimation("Slash3");
			break;
	}
	slashNumber++;*/
//	player->mRenderComponent->setAnimation("PLAYER_SWEEP");



}

void AttackState::exit(GameObject* character)
{
	


}