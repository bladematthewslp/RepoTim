#include "RyobeLogic.h"
#include "CStateRyobeStanding.h"
#include "BloodAnimationLogic.h"


RyobeLogic::RyobeLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
	, mHealth(100)
	, mIsHit(false)
	, mHitCounter(0)
	, mDirection(Direction::Left)
{
	
	player = System::findGameObjectByName("Player");



	mDamageTable[DamageType::Weak] =		1;
	mDamageTable[DamageType::Medium] =		3;
	mDamageTable[DamageType::Strong] =		5;
	mDamageTable[DamageType::Super] =		8;
	mDamageTable[DamageType::Unblockable] = 10;

	
	CState* state = std::unique_ptr<CState>(new CStateRyobeStanding(mGameObject)).release();
	state->entry(mGameObject);
	mGameObject->mState = state;
	
}

void RyobeLogic::update(Grid& grid)
{
	updateDirection();
	
	
	CState* newState = mGameObject->mState->update(mGameObject, sf::seconds(1.0/60.0f), grid);
	if(mGameObject->mState != newState)
	{
		std::cout << "!!" << std::endl;
		mGameObject->mState = newState;
	}


}



int RyobeLogic::getHealth()
{
	return mHealth;
}


void RyobeLogic::hit()
{
	if(mHealth <= 0)
		return;

	
	GameObjectDesc bloodDesc("BloodAnimation",sf::RectangleShape(),Layer::Foreground,ComponentType::RenderComponent);
	GameObject* blood = std::unique_ptr<GameObject>(new GameObject(bloodDesc)).release();
	blood->addComponent(ComponentType::LogicComponent, std::unique_ptr<LogicComponent>(new BloodAnimationLogic(blood)).release() );
	blood->setPosition(-75,-50);
	mGameObject->addChild(blood);
}

int RyobeLogic::getDirection()
{
	return mDirection;
}

void RyobeLogic::updateDirection()
{
	if(mGameObject->mState->getName() != "CStateRyobeStanding")
		return;

	float playerPositionX = player->getPosition().x;
	
	sf::RectangleShape* sprite = mGameObject->getSprite();
	
	if(playerPositionX >= mGameObject->getPosition().x && mDirection != Direction::Right)
	{
		mGameObject->mRenderComponent->mSprite.setScale(1, sprite->getScale().y);
		mDirection = Direction::Right;
	}
	if(playerPositionX < mGameObject->getPosition().x && mDirection != Direction::Left)
	{
		mGameObject->mRenderComponent->mSprite.setScale(-1, sprite->getScale().y);
		mDirection = Direction::Left;
	}

}