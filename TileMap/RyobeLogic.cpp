#include "RyobeLogic.h"
#include "CStateRyobeStanding.h"
#include "BloodAnimationLogic.h"
#include "CStateRyobeAttacking.h"
#include "CStateRyobeDead.h"

RyobeLogic::RyobeLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
	, mHealth(100)
	, mIsHit(false)
	, mHitCounter(0)
	, mDirection(Direction::Left)
	, mVelocity(0,0)
	, mIsUntouchable(false)
	, lightningChargeup(nullptr)
{
	
	player = System::findGameObjectByName("Player");



	mDamageTable[DamageType::Weak] =		1;
	mDamageTable[DamageType::Medium] =		2;
	mDamageTable[DamageType::Strong] =		3;
	mDamageTable[DamageType::Super] =		4;
	mDamageTable[DamageType::Unblockable] = 5;

	
	mHealthBarWidth = 352;
	mHealthBarHeight = 20;
	mMaxBarWidth = mHealthBarWidth;
	/*GameObjectDesc healthBarDesc("RyobeHealthBar",sf::RectangleShape(sf::Vector2f(mHealthBarWidth,mHealthBarHeight)), Layer::UI, ComponentType::RenderComponent);
	mHealthBar = std::unique_ptr<GameObject>(new GameObject(healthBarDesc)).release();
	mHealthBar->mRenderComponent->mTexture = mHealthBar->getRenderComponent()->mTextureHolder.get(Textures::RyobeHUDHealthbar);
	mHealthBar->mRenderComponent->mSprite.setTexture(&mHealthBar->mRenderComponent->mTexture);
	mMaxRectWidth = mHealthBar->mRenderComponent->mSprite.getTextureRect().width;
	mHealthBar->setPosition(487, 677);
	*/
	



	
}

void RyobeLogic::update(Grid& grid)
{
	if(mGameObject->mState == nullptr)
		return;

	updateDirection();

	mVelocity.x = 0;
	
	if(mGameObject->mState->getName() == "CStateRyobeAttacking")
	{
		CStateRyobeAttacking* attackState = dynamic_cast<CStateRyobeAttacking*>(mGameObject->mState);
		if(attackState->attackType == Attacks::RYOBE_EMBRACER
			|| attackState->attackType == Attacks::RYOBE_FELLCRESCENT)
			mIsUntouchable = true;
		else
			mIsUntouchable = false;
	}
	else
		mIsUntouchable = false;
	
	if(lightningChargeup != nullptr)
	{
		if(lightningChargeup->mRenderComponent->runSpriteAnim(*lightningChargeup) == SpriteAnim::Status::SUCCESS)
		//if(mGameObject->mState->getName() != "CStateRyobeAttacking")
		{
			System::removeGameObject(lightningChargeup);
			lightningChargeup = nullptr;
		}
	}
	
	
	
	CState* newState = mGameObject->mState->update(mGameObject, sf::seconds(1.0/60.0f), grid);
	if(mGameObject->mState != newState)
	{
		mGameObject->mState = newState;
	}


}



int RyobeLogic::getHealth()
{
	return mHealth;
}


void RyobeLogic::hit(GameObject* character, Attacks::Name attackName)
{
	if(mHealth <= 0)
		return;

	AttackType& attackType = Attacks::getAttack(attackName);
	
	int damageAmount = mDamageTable[attackType.mDamageType];
	mHealth -= damageAmount;

	if(mHealth <= 0)
		mGameObject->mState = std::unique_ptr<CState>(new CStateRyobeDead(mGameObject)).release();

	sf::IntRect rect = mHealthBar->getSprite()->getTextureRect();
	rect.width = mMaxRectWidth * (mHealth * 0.01);
	mHealthBar->getSprite()->setTextureRect(rect);

	mHealthBar->getSprite()->setSize(sf::Vector2f(mMaxBarWidth * (mHealth * 0.01), mHealthBarHeight));
	
	float healthBarDiff = (mHealthBarWidth* (damageAmount * 0.01) );
	mHealthBar->move(mMaxBarWidth * (damageAmount * 0.01), 0);

	GameObjectDesc bloodDesc("BloodAnimation",sf::RectangleShape(),Layer::Foreground,ComponentType::RenderComponent);
	GameObject* blood = std::unique_ptr<GameObject>(new GameObject(bloodDesc)).release();
	blood->addComponent(ComponentType::LogicComponent, std::unique_ptr<LogicComponent>(new BloodAnimationLogic(blood)).release() );
	blood->setPosition(-75,-50);
	mGameObject->addChild(blood);
}

void RyobeLogic::setVelocity(sf::Vector2f vel)
{
	mVelocity = vel;
}

void RyobeLogic::setVelocity(float x, float y)
{
	mVelocity.x = x;
	mVelocity.y = y;
}

void RyobeLogic::setVelocityX(float x)
{
	mVelocity.x = x;
}

void RyobeLogic::setVelocityY(float y)
{
	mVelocity.y = y;
}

void RyobeLogic::move(sf::Vector2f& vel)
{
	mGameObject->move(vel);
	mGameObject->mBoxColliderComponent->update();
}

void RyobeLogic::move(float x, float y)
{
	mGameObject->move(x,y);
	mGameObject->mBoxColliderComponent->update();
}
sf::Vector2f RyobeLogic::getVelocity()
{
	return mVelocity;
}

int RyobeLogic::getDirection()
{
	return mDirection;
}

void RyobeLogic::updateDirection()
{
	
	if(mGameObject->mState->getName() == "CStateRyobeAttacking")
	{
		if(dynamic_cast<CStateRyobeAttacking*>(mGameObject->mState)->isTeleporting() == false)
		{
			return;
		}
	}
	else if(mGameObject->mState->getName() != "CStateRyobeStanding")
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

GameObject* RyobeLogic::getHealthBar()
{
	return mHealthBar;
}

bool RyobeLogic::isUntouchable()
{
	return mIsUntouchable;
}

void RyobeLogic::setHealthBar(GameObject* healthbar) 
{ 
	mHealthBar = std::move(healthbar); 
	mMaxRectWidth = mHealthBar->mRenderComponent->mSprite.getTextureRect().width;
}

void RyobeLogic::createLightningChargeup()
{
	if(lightningChargeup != nullptr)
		return;
	GameObjectDesc lightningChargupDesc("LightningChargeup",sf::RectangleShape(sf::Vector2f(40,500)), Layer::Default, ComponentType::RenderComponent);
	lightningChargeup = std::unique_ptr<GameObject>(new GameObject(lightningChargupDesc)).release();
	lightningChargeup->mRenderComponent->createSpriteAnim(sf::IntRect(40, 0, 40, 340),"Lightning",true, 3, 1);
	lightningChargeup->mRenderComponent->setAnimation("Lightning");
	//lightningChargeup->mRenderComponent->mTexture.loadFromImage(RenderComponent::mImageHolder.get(Images::LightningWall));// = RenderComponent::mTextureHolder.get(Textures::Lightning);
	lightningChargeup->mRenderComponent->mSprite.setTexture(&RenderComponent::mTextureHolder.get(Textures::LightningWall));//lightningChargeup->mRenderComponent->mTexture);

	lightningChargeup->setPosition(mGameObject->getPosition().x - 20, -64);
}