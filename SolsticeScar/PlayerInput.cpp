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

void PlayerInput::disableInput()
{
	dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent)->setVelocityX(0);
	mIsEnabled = false;

}
void PlayerInput::handleRealtimeInput(const sf::Event& event)
{
	if(mIsEnabled == false)
		return;

	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(mGameObject->mLogicComponent);



	CState* state = mGameObject->mState->handleInput(mGameObject,event);
	if(state != mGameObject->mState)
	{
		logic->enterNewState(state);
		//mGameObject->mState = state;
	}
}

void PlayerInput::update(const sf::Event& event)
{
	
	
	
}


void PlayerInput::handleKeyQueue()
{
	
	// pop last key in key queue every 40 frames
	keyQueueTimer += deltaTime.asSeconds();;
	if(keyQueueTimer >= 1)
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
	if(mIsEnabled == false)
		return;


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
			// reset key queue timer
			keyQueueTimer = 0;

			keyQueue->push(key);
			if(keyQueue->size() > 2)
			{
				keyQueue->pop();
			}
		}

		if(key == sf::Keyboard::S)
		{
			//check if keys in keyQueue + Space equals a registered attack
			bool canAttack = logic->canAttackFromState();
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
					PlayerRender* render = dynamic_cast<PlayerRender*>(mGameObject->getRenderComponent());
					int currentFrame = render->mSpriteSet[render->currentAnim]->currentFrame;
					int frameToHold = render->mSpriteSet[render->currentAnim]->mFrameToHold;
					int numFrames = render->mSpriteSet[render->currentAnim]->numFrames;
					std::string currentAnim = render->currentAnim;
					typedef std::multimap<std::vector<sf::Keyboard::Key>, std::string>::iterator moveListIterator;

					bool matchingAttackFound = false;
					
					// check if pressed keys matches an action in the move list
					for(std::multimap<std::vector<sf::Keyboard::Key>, std::string>::iterator iter = list.begin(); iter != list.end();  )//iter++)
					{
						// if so...
						if(keyQueue == iter->first												// if the pressed keys matches key set in move list
							&& Attacks::getAttack(iter->second).mIsAirAttack == false			// if the attack is not an air attack
							&& iter->second != Attacks::PLAYER_SLASH							// if the attack is not a basic slash
							)//&& mGameObject->mState->getName() != "AttackState")
						{
							// if player is already attacking
							if(mGameObject->mState->getName() == "AttackState")
							{
								if( render->mSpriteSet[currentAnim]->allowNextAttack(currentFrame) == true)
								{
									// first, check if the player is facing the direction of the last input
									if(iter->second == "PLAYER_EXPEL" )
									{
										sf::Keyboard::Key lastKey = keyQueue.at(keyQueue.size() - 1);
										if(lastKey == sf::Keyboard::Right && logic->getDirection() == Direction::Right
											|| lastKey == sf::Keyboard::Left && logic->getDirection() == Direction::Left)
										{
											CState* newState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
											logic->enterNewState(newState);
											mGameObject->mRenderComponent->setAnimation(iter->second);
											matchingAttackFound = true;
											return;
										}
									}
									else
									{
										CState* newState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
										logic->enterNewState(newState);
										mGameObject->mRenderComponent->setAnimation(iter->second);
										return;
									}
								}
							}
							else
							{
								CState* newState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
								logic->enterNewState(newState);
								mGameObject->mRenderComponent->setAnimation(iter->second);
								return;
							}
								
							
						}

						// if no match is found, remove oldest key in queue and loop again
						iter++;
						if(iter == list.end() && keyQueue.size() > 1 )
						{
							keyQueue.erase(keyQueue.begin() );
							iter = list.begin();
						}
					}

					// if keys did not match any move list, set default slash animation accordingly
					if(matchingAttackFound == false)
					{
						if(mGameObject->mState->getName() != "AttackState")
						{
							CState* newState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
							logic->enterNewState(newState);
							//mGameObject->mState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
						
							mGameObject->getRenderComponent()->setAnimation("Slash1");
						}
						else
						{
							// if the animation is delayed and player is not on last slash
							if(mGameObject->mRenderComponent->isAnimDelayed() == true 
								&& render->currentAnim != "Slash3" 
								&& render->currentAnim != "PLAYER_HAILBRINGER_PART2" 
								&& render->currentAnim != "PLAYER_EXPEL_PART2")
							{
								CState* newState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
								logic->enterNewState(newState);
								//mGameObject->mState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
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
								if(currentFrame > frameToHold)
								{
									if(mGameObject->getRenderComponent()->currentAnim == "Slash2Part2")
									{
										CState* newState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
										logic->enterNewState(newState);
										//mGameObject->mState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
										mGameObject->getRenderComponent()->setAnimation("QuickUprising");
									}
									else if(mGameObject->getRenderComponent()->currentAnim == "QuickUprising")
									{
										CState* newState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
										logic->enterNewState(newState);
										//mGameObject->mState = std::unique_ptr<CState>(new AttackState(mGameObject)).release();
										mGameObject->getRenderComponent()->setAnimation("QuickStinger");
									}

								}
								

							}
						}
					}
				}
				else if(logic->isGrounded() == false)
				{
					PlayerRender* render = dynamic_cast<PlayerRender*>(mGameObject->getRenderComponent());
					int numFrames = render->mSpriteSet[render->currentAnim]->numFrames;
					int currentFrame = render->mSpriteSet[render->currentAnim]->currentFrame;
					int frameToHold = render->mSpriteSet[render->currentAnim]->mFrameToHold;
					std::string currentAnimName = render->currentAnim;


					

					// if player is currently attacking
					if(mGameObject->mState->getName() == "AttackStateAir" && currentFrame > numFrames/2 && mGameObject->getRenderComponent()->currentAnim != "PLAYER_HAILBRINGER")
					{
						if(keyQueueSize == 0)
						{
							// if this animation is not already playing...
							if( currentFrame > numFrames/2 && render->currentAnim != "PLAYER_SWEEP")
							{
								// play the default slash
								CState* newState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
								logic->enterNewState(newState);
								//mGameObject->mState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
								mGameObject->mRenderComponent->setAnimation("PLAYER_SWEEP");
							}
						}
						else //if(currentFrame > numFrames/2)
						{
							bool matchingKeyVectorFound = false;
							
							
							// check if pressed keys matches an action in the move list
							for(std::multimap<std::vector<sf::Keyboard::Key>, std::string>::iterator iter = list.begin(); iter != list.end();  )//iter++)
							{
								// if so...
								if(keyQueue == iter->first && Attacks::getAttack(iter->second).mIsAirAttack == true)
								{
									CState* newState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
									logic->enterNewState(newState);
									mGameObject->mRenderComponent->setAnimation(iter->second);
									matchingKeyVectorFound = true;
									break;
								}

								// if no match is found, remove oldest key in queue and loop again
								iter++;
								if(iter == list.end() && keyQueue.size() > 1 )
								{
									keyQueue.erase(keyQueue.begin() );
									iter = list.begin();
								}
							}	// end for loop
							
							// if keys did not match any move list, set default slash animation
							if(matchingKeyVectorFound == false )
							{
								// if this animation is not already playing...
								if(render->currentAnim != "PLAYER_SWEEP" && currentFrame > numFrames/2)
								{
									// play the default slash
									CState* newState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
									logic->enterNewState(newState);
									mGameObject->mRenderComponent->setAnimation("PLAYER_SWEEP");
								}
							}
						}

					}

					else if(mGameObject->mState->getName() != "AttackStateAir")
					{
						if(keyQueueSize == 0)
						{
							// if this animation is not already playing...
							//if( currentFrame > numFrames/2 && render->currentAnim != "PLAYER_SWEEP")
							{
								// play the default slash
								CState* newState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
								logic->enterNewState(newState);
								//mGameObject->mState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
								mGameObject->mRenderComponent->setAnimation("PLAYER_SWEEP");
							}
						}
						else
						{
							bool matchingKeyVectorFound = false;

							// check if pressed keys matches an action in the move list
							for(std::multimap<std::vector<sf::Keyboard::Key>, std::string>::iterator iter = list.begin(); iter != list.end(); ) // iter++)
							{
								// if so...
								if(keyQueue == iter->first && Attacks::getAttack(iter->second).mIsAirAttack == true)
								{
									CState* newState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
									logic->enterNewState(newState);
									mGameObject->mRenderComponent->setAnimation(iter->second);
									matchingKeyVectorFound = true;
									break;
								}

								// if no match is found, remove oldest key in queue and loop again
								iter++;
								if(iter == list.end() && keyQueue.size() > 1 )
								{
									keyQueue.erase(keyQueue.begin() );
									iter = list.begin();
								}
							}	// end for loop
						
							// if keys did not match any move list, set default slash animation
							if(matchingKeyVectorFound == false )
							{
								if(render->currentAnim != "PLAYER_SWEEP" && currentFrame > numFrames/2)
								{
									CState* newState = std::unique_ptr<CState>(new AttackStateAir(mGameObject)).release();
									logic->enterNewState(newState);
									mGameObject->mRenderComponent->setAnimation("PLAYER_SWEEP");
								}
							}
						}
					
					}

				}
				
			}
		}	// end if(key == sf::Keyboard::S)
	}

	

	/*
	CState* state = mGameObject->mState->handleInput(mGameObject,event);
	if(state != mGameObject->mState)
	{
		logic->enterNewState(state);
		//mGameObject->mState = state;
	}
	*/
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