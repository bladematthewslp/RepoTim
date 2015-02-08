#include "PlayerInput.h"
#include "GameObject.h"
#include "PlayerLogic.h"
#include "CState.h"
//#include "PlayerObject.h"
#include "StandingState.h"
#include "AttackState.h"
#include "AttackStateAir.h"
#include "Grid.h"
#include <iostream>


const sf::Time deltaTime = sf::seconds(1.0f/60.0f);

bool validKey(sf::Keyboard::Key key)
{
	switch(key)
	{
	case sf::Keyboard::Right:
	case sf::Keyboard::Left:
	case sf::Keyboard::Up:
	case sf::Keyboard::Down:
		//PostQuitMessage(0);
		return true;
	}

	return false;
}
PlayerInput::PlayerInput(GameObject* gameObject) : InputComponent(gameObject)
{
	keyDelayTimer = 0;
	keyQueueTimer = 0;
	keyQueue = std::unique_ptr<std::queue<sf::Keyboard::Key>>(new std::queue<sf::Keyboard::Key>()).release();
	//playerObject = mGameObject;
	//if(playerObject == nullptr)
	{
	//	std::cout << "dynamic cast" << std::endl;
	}
}

void PlayerInput::handleRealtimeInput(const sf::Event& event)
{
	
	CState* state = mGameObject->mState->handleInput(mGameObject,event);
	if(state != mGameObject->mState)
	{
		mGameObject->mState = state;
	}
}

void PlayerInput::update(const sf::Event& event)
{
	
	
	
}


void PlayerInput::handleKeyQueue()
{
	// pop last key in key queue every 40 frames
	keyQueueTimer++;
	if(keyQueueTimer == 40)
	{
		
		keyQueueTimer = 0;
		if(!keyQueue->empty() )
		{
			keyQueue->pop();
		}
	}
	
}


void PlayerInput::handleEvents(const sf::Event& event)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent);
	if(logic->getHealth() <= 0 || mGameObject->mState->getName() == "HitState")
		return;
	

	if(keyDelayTimer > 0)
	{
		keyDelayTimer++;
		if(keyDelayTimer > 45)
			keyDelayTimer = 0;
	}

	if(keyDelayTimer > 30 && keyDelayTimer < 45)
	{
		
	}
	if(event.type == event.KeyPressed)
	{
		sf::Keyboard::Key key = event.key.code;

		if(validKey(key) == true) 
		{
 			keyQueue->push(key);
			
			if(keyQueue->size() > 2)
			{
				keyQueue->pop();
			}
		}

		if(key == sf::Keyboard::Space)
		{
			//check if keys in keyQueue + Space equals a registered attack
			bool canAttack = logic->statesCanAttack();
			if(canAttack == true)
			{
				PlayerLogic* logic = dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent);
				PlayerInput* input = dynamic_cast<PlayerInput*>(mGameObject->mInputComponent);
	
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
				
				if(logic->isGrounded() == true)
				{

					// check if pressed keys matches an action in the move list
					for(std::multimap<std::vector<sf::Keyboard::Key>, std::string>::iterator iter = list.begin(); iter != list.end(); iter++)
					{
						// if so...
						if(keyQueue == iter->first												// if the pressed keys matches key set in move list
							&& Attacks::getAttack(iter->second).mIsAirAttack == false			// if the attack is not an air attack
							&& iter->second != Attacks::PLAYER_SLASH)							// if the attack is not a basic slash
						{
							mGameObject->mState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
							mGameObject->mRenderComponent->setAnimation(iter->second);
							return;
						}
					}

					// if keys did not match any move list, set default slash animation accordingly
					if(mGameObject->mState->getName() != "AttackState")
					{
						mGameObject->mState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
						mGameObject->getRenderComponent()->setAnimation("Slash1");
					}
					else
					{
						if(mGameObject->mRenderComponent->isAnimDelayed() == true)
						{
							mGameObject->mState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
							if(mGameObject->getRenderComponent()->currentAnim == "Slash1")
							{
								
								mGameObject->getRenderComponent()->setAnimation("Slash2Part1");
							}
							else if(mGameObject->getRenderComponent()->currentAnim == "Slash2Part1")
							{
								
									mGameObject->getRenderComponent()->setAnimation("Slash3");
							}
							else if(mGameObject->getRenderComponent()->currentAnim == "QuickStinger")
							{
								
									mGameObject->getRenderComponent()->setAnimation("Slash3");
							}
						}
						else
						{
							PlayerRender* render = dynamic_cast<PlayerRender*>(mGameObject->getRenderComponent());
							int currentFrame = render->mSpriteSet[render->currentAnim]->currentFrame;
							int frameToHold = render->mSpriteSet[render->currentAnim]->mFrameToHold;
							if(currentFrame > frameToHold)
							{
								if(mGameObject->getRenderComponent()->currentAnim == "Slash2Part2")
								{
									mGameObject->mState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
									mGameObject->getRenderComponent()->setAnimation("QuickUprising");
								}
								else if(mGameObject->getRenderComponent()->currentAnim == "QuickUprising")
								{
									mGameObject->mState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
									mGameObject->getRenderComponent()->setAnimation("QuickStinger");
								}

							}
								

						}
					}
				}
				else if(logic->isGrounded() == false)
				{
					// check if pressed keys matches an action in the move list
					for(std::multimap<std::vector<sf::Keyboard::Key>, std::string>::iterator iter = list.begin(); iter != list.end(); iter++)
					{
						// if so...
						if(keyQueue == iter->first && Attacks::getAttack(iter->second).mIsAirAttack == true)
						{
							if(mGameObject->mState->getName() != "AttackStateAir")
							{
								mGameObject->mState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
								std::cout << iter->second << std::endl;
								mGameObject->mRenderComponent->setAnimation(iter->second);
							}
						}
					}

					// if keys did not match any move list, set default slash animation
					if(mGameObject->mState->getName() != "AttackStateAir")
					{
						mGameObject->mState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
						mGameObject->mRenderComponent->setAnimation("PLAYER_SWEEP");
					}

				}
				
			}
		}
	}
	
	CState* state = mGameObject->mState->handleInput(mGameObject,event);
	if(state != mGameObject->mState)
	{
		mGameObject->mState = state;
	}
	
}

bool PlayerInput::checkValidCommand()
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent);
	PlayerInput* input = dynamic_cast<PlayerInput*>(mGameObject->mInputComponent);
	
	// get move List from logic component
	std::multimap<std::vector<sf::Keyboard::Key>, std::string> list = logic->getMoveList();

	// create key queue to match to move list
	std::vector<sf::Keyboard::Key> commandKeys;
	
	int keyQueueSize = keyQueue->size();

	for(int i = 0; i < keyQueueSize; i++)
	{
		commandKeys.push_back(keyQueue->front());//input->getKeyQueue()->front());
		keyQueue->pop();
	}
	
	// check if pressed keys matches an action in the move list
	for(std::multimap<std::vector<sf::Keyboard::Key>, std::string>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		// if so...
		if(commandKeys == iter->first)
		{
			if(Attacks::getAttack(iter->second).mIsAirAttack == false)
			{
				AttackState* newState = std::unique_ptr<AttackState>(new AttackState(mGameObject)).release();
				newState->setAttack(iter->second);
			}
			else if(Attacks::getAttack(iter->second).mIsAirAttack == true)
			{

			}
		
			return true;
		}
	}

	return false;

}

std::queue<sf::Keyboard::Key>* PlayerInput::getKeyQueue()
{

	return keyQueue;
}


void PlayerInput::clearKeyQueue()
{
	while(keyQueue->size() != 0)
		keyQueue->pop();
}