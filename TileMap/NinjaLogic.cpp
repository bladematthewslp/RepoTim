#include "NinjaLogic.h"
#include "System.h"
#include "CState.h"
#include "CStateNinjaStanding.h"
#include "CStateNinjaHit.h"
#include "CStateNinjaDead.h"
#include "CStateNinjaDeadAir.h"
#include "CStateNinjaHitAir.h"
#include "Grid.h"
#include <cmath>
#include <iostream>


const sf::Time deltaTime = sf::seconds(1.0f/60.0f);

NinjaLogic::NinjaLogic(GameObject* gameObject) 
	: LogicComponent(gameObject)
	, mDirection(Direction::Left)
	, mHealth(100)
	, mVelocity(0,0)
	, mIsGrounded(true)
	, mRunningSpeed(2.0f)
{
	player = System::findGameObjectByName("Player");

	if(player == nullptr)
		std::cout << "player not found" << std::endl;

	
	
	
	mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaStanding(mGameObject)).release();
	
	// setup damage table
	mDamageTable[DamageType::Weak] =		3;//10;
	mDamageTable[DamageType::Medium] =		5;//15;
	mDamageTable[DamageType::Strong] =		9;//20;
	mDamageTable[DamageType::Super] =		25;
	mDamageTable[DamageType::Unblockable] = 25;


}


void NinjaLogic::update(Grid& grid)
{
	if(mHealth <= 0)
	{
		//mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaDead(mGameObject)).release();
	}
	updateDirection();

	// handle mIsGrounded variable
	if(mVelocity.y != 0)
		mIsGrounded = false;
	else
		mIsGrounded = true;
	
	//std::cout << mVelocity.x << " , " << mVelocity.y << std::endl;
	
	//std::cout << mIsGrounded << std::endl;
	CState* state = mGameObject->mState->update(mGameObject, deltaTime, grid);
	if(mGameObject->mState != state)
	{
		mGameObject->mState = state;
	}

}

void NinjaLogic::setGrounded(bool flag)
{
	mIsGrounded = flag;
}
bool NinjaLogic::isGrounded()
{
	return mIsGrounded;
}

void NinjaLogic::updateDirection()
{
	if(mGameObject->mState->getName() != "CStateNinjaRunning")
		return;

	float playerPositionX = player->getPosition().x;
	
	if(playerPositionX >= mGameObject->getPosition().x && mDirection != Direction::Right)
	{
		mGameObject->mRenderComponent->mSprite.setScale(-1, 1);
		mDirection = Direction::Right;
	}
	if(playerPositionX < mGameObject->getPosition().x && mDirection != Direction::Left)
	{
		mGameObject->mRenderComponent->mSprite.setScale(1, 1);
		mDirection = Direction::Left;
	}
}

int NinjaLogic::getDirection()
{
	return mDirection;
}

sf::Vector2f NinjaLogic::getVelocity()
{
	return mVelocity;

}
void NinjaLogic::setVelocityX(float num)
{
	mVelocity.x = num;
}
void NinjaLogic::setVelocityY(float num)
{
	mVelocity.y = num;
}

float NinjaLogic::getRunningSpeed()
{
	return mRunningSpeed;
}
void NinjaLogic::move(float x, float y)
{
	mGameObject->move(x, y);
	mGameObject->mBoxColliderComponent->update();
}

void NinjaLogic::move(sf::Vector2f pos)
{
	mGameObject->move(pos);
	mGameObject->mBoxColliderComponent->update();
}
void NinjaLogic::setVelocity(sf::Vector2f vel)
{
	mVelocity = vel;
}

void NinjaLogic::setVelocity(float x, float y)
{
	mVelocity.x = x;
	mVelocity.y = y;
}

int NinjaLogic::getHealth()
{
	return mHealth;
}


void NinjaLogic::hit(GameObject* character, Attacks::Name attackName)
{
	// if health is already 0, return
	if(mHealth <= 0)
		return;


	// resolve attack name to attack tipe
	AttackType attackType = Attacks::getAttack(attackName);

	// subtract health based on Damage Type
	mHealth -= mDamageTable[attackType.mDamageType];
	
	// if health is NOW less than or equal to zero...
	if(mHealth <= 0)
	{
		// dead state
		if(mIsGrounded == true)
		{
			mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaDead(mGameObject)).release();
			return;
		}
		else if(mIsGrounded == false)
		{
			mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaDeadAir(mGameObject)).release();
			return;
		}
	}

	if(mIsGrounded == true)
	{
		if(attackType.mCanLaunch == true)
		{
			mGameObject->mState->exit(mGameObject);
			mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaHitAir(mGameObject)).release();
			dynamic_cast<CStateNinjaHitAir*>(mGameObject->mState)->entry(character, attackType);
		}
		else if(mGameObject->mState->getName() == "CStateNinjaHit")
		{
			//mVelocity.x = mDirection * -1;
			dynamic_cast<CStateNinjaHit*>(mGameObject->mState)->successiveHit(character, attackType);
		}
		else
		{
			mGameObject->mState->exit(mGameObject);
			mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaHit(mGameObject)).release();
			mVelocity.x = mDirection * 1;
			dynamic_cast<CStateNinjaHit*>(mGameObject->mState)->entry(character, attackType);
		}
	}
	else if(mIsGrounded == false)
	{
		if(mGameObject->mState->getName() == "CStateNinjaHitAir")
		{
			//mVelocity.x = mDirection * -1;
			dynamic_cast<CStateNinjaHitAir*>(mGameObject->mState)->successiveHit(character, attackType);
			//std::cout << "AIRHIT" << std::endl;
		}
		else if(mGameObject->mState->getName() != "CStateNinjaHitAir")
		{
			mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaHitAir(mGameObject)).release();
			//mVelocity.x = mDirection * 1;
			dynamic_cast<CStateNinjaHitAir*>(mGameObject->mState)->entry(character, attackType);
		}
	}
	/*
	if(attackType.mCanLaunch == true)
	{
		mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaHitAir(mGameObject)).release();
	}
	else
	{
		if(mGameObject->mState->getName() == "CStateNinjaHit")
		{
			mVelocity.x = mDirection * -1;
			dynamic_cast<CStateNinjaHit*>(mGameObject->mState)->successiveHit(character, attackType);
		}
		else
		{
			mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaHit(mGameObject)).release();
			mVelocity.x = mDirection * 1;
			dynamic_cast<CStateNinjaHit*>(mGameObject->mState)->entry(character, attackType);
		}
	}*/


	// no state change when ninja is hit with WEAK attack. Only decrease health
	//if(attackType.mDamageType == DamageType::Weak)
	//	return;			
	/*
	if(mGameObject->mState->getName() == "CStateNinjaHit")
	{
		if(attackType.mCanLaunch != true)
			mVelocity.x = mDirection * -1;

		dynamic_cast<CStateNinjaHit*>(mGameObject->mState)->successiveHit(character, attackType);
		
	}
	else
	{
		mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaHit(mGameObject)).release();
		if(attackType.mCanLaunch != true)
			mVelocity.x = mDirection * 1;
		dynamic_cast<CStateNinjaHit*>(mGameObject->mState)->entry(character, attackType);
		
		
	}
	*/

	/*switch(attackType.mDamageType)
	{
		
		case DamageType::Strong:
		{
			//mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaDead(mGameObject)).release();
			break;
		}
		default:
		{
			mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaHit(mGameObject)).release();
		}

	}
	*/
	
	//mHealth -= mDamageTable[attackType.mDamageType];

	/*
	if(mHealth < 0)
		return;

	//mHealth -= damageAmount;
	
	
	if(mHealth <= 0)
	{
		mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaDead(mGameObject)).release();
	}
	else
	{
		mGameObject->mState = std::unique_ptr<CState>(new CStateNinjaHit(mGameObject)).release();
	}
	*/
}