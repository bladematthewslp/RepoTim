#include "PlayerLogic.h"
#include "CState.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "StandingState.h"
#include "HitState.h"
#include "KnockoutState.h"
#include "HitAirState.h"
#include "DeadAirState.h"
#include "BattleReadyState.h"
#include "GuardState.h"
#include "NinjaLogic.h"
#include "BoxColliderComponent.h"
#include "PlayerInput.h"
#include "HealthBarLogic.h"
#include "GUIRedOrbRender.h"
#include "RyobeLogic.h"
#include "DaggerLogic.h"
#include "ParryEffectLogic.h"
#include "SoundPlayer.h"
#include <iostream>

const sf::Time deltaTime = sf::seconds(1.0f/60.0f);
PlayerLogic::PlayerLogic(GameObject* mGameObject)
	: LogicComponent(mGameObject)
	, mDirection(Direction::Right)
	, box(mGameObject->getPosition().x - 50, mGameObject->getPosition().y, 100, 100)
	, mVelocity(0,0)
	, mMoveList()
	, mIsGrounded(true)
	, mHealth(100)
	, mNumRedOrbs(0)
	, mSoundPlayer()
{
	

	
	

	// HealthBar
	mHealthBar = System::findGameObjectByName("HealthBar");
	if(mHealthBar == nullptr)
		std::cout << "HealthBar not found" << std::endl;
	

	// RedOrbGUI
	mRedOrbsGUI = System::findGameObjectByName("GUIRedOrb");
	if(mRedOrbsGUI == nullptr)
		std::cout << "GUIRedOrb not found" << std::endl;
	dynamic_cast<GUIRedOrbRender*>(mRedOrbsGUI->mRenderComponent)->setRedOrbNum(mNumRedOrbs);


	mGameObject->setPosition(300,(32*19) - mGameObject->getSprite()->getLocalBounds().height/8);

	GameObjectDesc boxDesc("playerBBox", 
							sf::RectangleShape(sf::Vector2f(mGameObject->getSprite()->getGlobalBounds().width/4,mGameObject->getSprite()->getGlobalBounds().height/4)), 
							Layer::Default,
							ComponentType::RenderComponent);
	playerBBox = std::unique_ptr<GameObject>
	(new GameObject(boxDesc)).release();//sf::RectangleShape(sf::Vector2f(mGameObject->getSprite()->getGlobalBounds().width/4,mGameObject->getSprite()->getGlobalBounds().height/4)),ComponentType::RenderComponent,"playerBBox")).release();
	playerBBox->getSprite()->setOrigin(playerBBox->getSprite()->getLocalBounds().width/2, playerBBox->getSprite()->getLocalBounds().height/2);
	playerBBox->getRenderComponent()->mSprite.setFillColor(sf::Color::Transparent);
	
	
	playerObject = mGameObject;
	
	BattleReadyState* newState = std::unique_ptr<BattleReadyState>(new BattleReadyState(mGameObject)).release();
	newState->setMaxTime(8);
	mGameObject->mState = newState;
	
	
	/* _________________________________________________________________________________________________________________________________*/
	/*														MOVE LIST																	*/
	/* _________________________________________________________________________________________________________________________________*/
	/*|  MOVE NAME											KEY 1												KEY 2					|*/
	/*|---------------------------------------------------------------------------------------------------------------------------------|*/
	KeyVector Impact;						Impact.push_back(sf::Keyboard::Down);				               /*---*/
	KeyVector Slash;										/*---*/											   /*---*/
	KeyVector ChopperStyle;					ChopperStyle.push_back(sf::Keyboard::Down);			ChopperStyle.push_back(sf::Keyboard::Down);
	KeyVector Sweep;										/*---*/											   /*---*/
	KeyVector Repel;						Repel.push_back(sf::Keyboard::Right);
	KeyVector HailBringer;					HailBringer.push_back(sf::Keyboard::Down);

	mMoveList.insert(std::pair<KeyVector, std::string>(Impact, Attacks::PLAYER_IMPACT));
	mMoveList.insert(std::pair<KeyVector, std::string>(Slash, Attacks::PLAYER_SLASH));
	mMoveList.insert(std::pair<KeyVector, std::string>(Sweep, Attacks::PLAYER_SWEEP));
	mMoveList.insert(std::pair<KeyVector, std::string>(Repel, Attacks::PLAYER_REPEL));
	mMoveList.insert(std::pair<KeyVector, std::string>(ChopperStyle, Attacks::PLAYER_CHOPPERSTYLE));
	mMoveList.insert(std::pair<KeyVector, std::string>(HailBringer, Attacks::PLAYER_HAILBRINGER));
	//mMoveList[Impact] =			Attacks::PLAYER_IMPACT;	//"Impact";
	//mMoveList[Slash] =			Attacks::PLAYER_SLASH; // "Slash";
	//mMoveList[Sweep] =			Attacks::PLAYER_SWEEP;
	//mMoveList[ChopperStyle] =	Attacks::PLAYER_CHOPPERSTYLE;//"ChopperStyle";

	
	mDamageTable[DamageType::Weak] = 10;
	mDamageTable[DamageType::Medium] = 20;
	mDamageTable[DamageType::Strong] = 30;
	mDamageTable[DamageType::Super] = 40;
	mDamageTable[DamageType::Unblockable] = 40;

	
}

void PlayerLogic::update(Grid& grid)
{
	//updateBox();
	//mSoundPlayer.removeStoppedSounds();

	

	// this is unorthodox but it needs to be here to update every frame
	PlayerInput* input = dynamic_cast<PlayerInput*>(mGameObject->mInputComponent);
	input->handleKeyQueue();

	if(mVelocity.y != 0)// && (mGameObject->mState->getName() != "JumpingState" || mGameObject->mState->getName() != "FallingState") )
		mIsGrounded = false;
	else
		mIsGrounded = true;

	
	
	CState* state = mGameObject->mState->update(playerObject, deltaTime, grid);
	if(state != mGameObject->mState)
	{
		enterNewState(state);
	}

	mSoundPlayer.removeStoppedSounds();
}
int deleteCount = 0;
void PlayerLogic::enterNewState(CState* newState)
{
	mGameObject->mState->exit(mGameObject);
	delete mGameObject->mState;

	mGameObject->mState = newState;


}


bool PlayerLogic::isReadyForBattle()
{
	if(mIsGrounded == true	&& mVelocity.x == 0 && mGameObject->mState->getName() != "BattleReadyState")
	{
		mGameObject->mState = std::unique_ptr<CState>(new BattleReadyState(mGameObject)).release();
		mGameObject->mState->entry(mGameObject);
		return true;
	}

	return false;
}

void PlayerLogic::pickupRedOrb()
{
	mNumRedOrbs += 5;
	dynamic_cast<GUIRedOrbRender*>(mRedOrbsGUI->mRenderComponent)->setRedOrbNum(mNumRedOrbs);
}

void PlayerLogic::pickupGreenOrb()
{
	mHealth += 30;
	
	if(mHealth > 100)
		mHealth = 100;

	dynamic_cast<HealthBarLogic*>(mHealthBar->mLogicComponent)->updateHealth(mHealth);

}

bool PlayerLogic::canAttackFromState()
{
	std::array<std::string, 8>  statesNoAttack = {	
					 	"DazedState",
					 	"DeadAirState",
					 	"HitAirState",
					 	"HitState",
					 	"KnockoutState",
						"AttackBlockedState",
						"AttackBlockedAirState",
						"BattleReadyState"
					 };
	
	int size = statesNoAttack.size();
	
	for(int i = 0; i < size; i++)
	{
		// if any state in "statesNoAttack" array is the current state
		if(mGameObject->mState->getName() == statesNoAttack[i] )
		{
			// cannot attack, return false
			return false;
		}
	}
	
	// otherwise return true
	return true;
}

void PlayerLogic::hit(GameObject* otherCharacter, Attacks::Name attackName)
{
	if(mHealth <= 0)
		return;

	LogicComponent* logic = nullptr;
	if(dynamic_cast<NinjaLogic*>(otherCharacter->mLogicComponent) != nullptr)
	{
		logic = dynamic_cast<NinjaLogic*>(otherCharacter->mLogicComponent);
	}
	else if(dynamic_cast<DaggerLogic*>(otherCharacter->mLogicComponent) != nullptr)
	{
		logic = dynamic_cast<DaggerLogic*>(otherCharacter->mLogicComponent);
	}
	else if(dynamic_cast<RyobeLogic*>(otherCharacter->mLogicComponent) != nullptr)
	{
		logic = dynamic_cast<RyobeLogic*>(otherCharacter->mLogicComponent);
	}

	if(logic == nullptr)
	{
		std::cout << "No Logic Component found" << std::endl;
		return;
	}

	AttackType attackType = Attacks::getAttack(attackName);
	
	

	

	// if the player is hit while grounded....
	if(mIsGrounded == true)
	{
		// ...first check if the attacking enemy faces same direction as player.
		if(logic->getDirection() == this->getDirection())
		{
			// ...if so, update this direction
			this->updateDirection(-getDirection());
		}
	
		// handle if player is blocking
		if(mGameObject->mState->getName() == "GuardState")
		{
			dynamic_cast<GuardState*>(mGameObject->mState)->block(mGameObject);
			return;
		}

		// Handle health and state change here
		mHealth -= mDamageTable[attackType.mDamageType];
		dynamic_cast<HealthBarLogic*>(mHealthBar->mLogicComponent)->updateHealth(mHealth);

		if(mHealth <= 0)
		{
			mGameObject->mState = std::unique_ptr<CState>(new KnockoutState(mGameObject)).release();
			return;
		}

		// if damage type is STRONG or SUPER
		if(attackType.mDamageType == DamageType::Strong || attackType.mDamageType == DamageType::Super)
		{
			// change state to knockdown state
			mGameObject->mState = std::unique_ptr<CState>(new KnockoutState(mGameObject)).release();
		}
		else	// if not,
		{
			// change state to hit state
			if(mGameObject->mState->getName() == "HitState")
				dynamic_cast<HitState*>(mGameObject->mState)->hitConsecutive(mGameObject);
			else
				mGameObject->mState = std::unique_ptr<CState>(new HitState(mGameObject)).release();
		}
	}
	else if( mIsGrounded == false)
	{
		// ...first check if the attacking enemy faces same direction as player.
		if(logic->getDirection() == this->getDirection())
		{
			// ...if so, update this direction
			this->updateDirection(-getDirection());
		}

		// Handle health and state change here
		mHealth -= mDamageTable[attackType.mDamageType];
		dynamic_cast<HealthBarLogic*>(mHealthBar->mLogicComponent)->updateHealth(mHealth);
		if(mHealth <= 0)
		{
			mGameObject->mState = std::unique_ptr<CState>(new DeadAirState(mGameObject)).release();
			return;
		}

			mGameObject->mState = std::unique_ptr<CState>(new HitAirState(mGameObject)).release();

	}
	
}

void PlayerLogic::setHealth(int num)
{
	mHealth = num;
}
int	 PlayerLogic::getHealth()
{
	return mHealth;
}

void PlayerLogic::setGrounded(bool grounded)
{
	mIsGrounded = grounded;
}
bool PlayerLogic::isGrounded()
{
	return mIsGrounded;
}

std::multimap<std::vector<sf::Keyboard::Key>, std::string>& PlayerLogic::getMoveList()
{
	return mMoveList;

}

sf::Vector2f PlayerLogic::getPosition() const
{
	return this->mGameObject->getPosition();
}

void PlayerLogic::setPosition(sf::Vector2f pos)
{
	this->mGameObject->setPosition(pos);
}

sf::FloatRect PlayerLogic::getLocalBounds() const 
{ 
	return this->mGameObject->getSprite()->getLocalBounds(); 
};

sf::FloatRect PlayerLogic::getGlobalBounds() const 
{ 
	return this->mGameObject->getSprite()->getGlobalBounds(); 
};

sf::Vector2f PlayerLogic::getVelocity()
{
	return mVelocity;		
};

void PlayerLogic::setVelocity(sf::Vector2f vel)
{
	mVelocity = vel;
};

void PlayerLogic::setVelocityX(float x)
{
	mVelocity.x = x;	
};

void PlayerLogic::setVelocityY(float y)
{
	mVelocity.y = y;
}

void PlayerLogic::move(sf::Vector2f dir)
{
	mGameObject->move(dir);
	updateBox();
	mGameObject->mBoxColliderComponent->update();
};
void PlayerLogic::move(float x, float y)
{
	mGameObject->move(x,y);		
	updateBox();
	mGameObject->mBoxColliderComponent->update();
};

int PlayerLogic::getDirection()
{
	return mDirection;
}

void PlayerLogic::updateDirection(int dir)
{
	sf::RectangleShape* sprite = mGameObject->getSprite();
	if(mDirection != dir)
	{
		mDirection = dir;
		sprite->setScale(-sprite->getScale().x, sprite->getScale().y);
	}
	
}

float PlayerLogic::getRunningSpeed()
{
	return 5.0f;

}

void PlayerLogic::updateBox()
{
	box.left = mGameObject->getPosition().x - 40;
	box.top = mGameObject->getPosition().y - 50;
	box.width = 80;
	box.height = 100;
}

void PlayerLogic::setNewState(CState* newState)
{
	CState* state = std::unique_ptr<CState>(newState).release();
	mGameObject->mState = state;
}