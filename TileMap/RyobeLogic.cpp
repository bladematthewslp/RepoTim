#include "RyobeLogic.h"
#include "CStateRyobeStanding.h"
#include "BloodAnimationLogic.h"
#include "CStateRyobeAttacking.h"


RyobeLogic::RyobeLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
	, mHealth(100)
	, mIsHit(false)
	, mHitCounter(0)
	, mDirection(Direction::Left)
	, mVelocity(0,0)
	, mIsUntouchable(false)
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
	GameObjectDesc healthBarDesc("RyobeHealthBar",sf::RectangleShape(sf::Vector2f(mHealthBarWidth,mHealthBarHeight)), Layer::UI, ComponentType::RenderComponent);
	mHealthBar = std::unique_ptr<GameObject>(new GameObject(healthBarDesc)).release();
	mHealthBar->mRenderComponent->mTexture = mHealthBar->getRenderComponent()->mTextureHolder.get(Textures::RyobeHUDHealthbar);
	mHealthBar->mRenderComponent->mSprite.setTexture(&mHealthBar->mRenderComponent->mTexture);
	mMaxRectWidth = mHealthBar->mRenderComponent->mSprite.getTextureRect().width;
	mHealthBar->setPosition(487, 677);

	GameObjectDesc ryobeHUDDesc("RyobeHUD", sf::RectangleShape(sf::Vector2f(607,160)), Layer::UI, ComponentType::RenderComponent);
	GameObject* ryobeHUD = std::unique_ptr<GameObject>(new GameObject(ryobeHUDDesc)).release();
	ryobeHUD->setPosition(400, 578);
	ryobeHUD->mRenderComponent->mSprite.setTexture(&ryobeHUD->getRenderComponent()->mTextureHolder.get(Textures::RyobeHUD));


	/*
	GameObjectDesc healthBarBorderDesc("RyobeHealthBarBorder", sf::RectangleShape(sf::Vector2f(mHealthBarWidth, mHealthBarHeight)), Layer::UI, ComponentType::RenderComponent);
	GameObject* healthBarBorder = std::unique_ptr<GameObject>(new GameObject(healthBarBorderDesc)).release();
	healthBarBorder->mRenderComponent->mSprite.setFillColor(sf::Color::Transparent);
	healthBarBorder->getSprite()->setOutlineColor(sf::Color::Black);
	healthBarBorder->getSprite()->setOutlineThickness(5);
	healthBarBorder->setPosition(mHealthBar->getPosition());
	*/
	/*
	GameObjectDesc ryobeMugShotDesc("RyobeMugShot", sf::RectangleShape(sf::Vector2f(80, 85)), Layer::UI, ComponentType::RenderComponent);
	GameObject* mugshot = std::unique_ptr<GameObject>(new GameObject(ryobeMugShotDesc)).release();
	mugshot->setPosition(900, 625);
	mugshot->mRenderComponent->mTexture = RenderComponent::mTextureHolder.get(Textures::RyobeMugshot);
	mugshot->mRenderComponent->mSprite.setTexture(&mugshot->mRenderComponent->mTexture);
	*/
	
	CState* state = std::unique_ptr<CState>(new CStateRyobeStanding(mGameObject)).release();
	state->entry(mGameObject);
	mGameObject->mState = state;
	
	GameObjectDesc lightningDesc("Lightning", sf::RectangleShape(sf::Vector2f(40,680)), Layer::Enemy, ComponentType::RenderComponent);
	lightning = std::unique_ptr<GameObject>(new GameObject(lightningDesc)).release();
	lightning->mRenderComponent->createSpriteAnim(sf::IntRect(40, 0, 40, 340),"Lightning",true, 6, 1.6);
	lightning->mRenderComponent->setAnimation("Lightning");
	lightning->mRenderComponent->mTexture = RenderComponent::mTextureHolder.get(Textures::Lightning);
	lightning->mRenderComponent->mSprite.setTexture(&lightning->mRenderComponent->mTexture);
	lightning->addComponent(ComponentType::BoxColliderComponent);
	//lightning->mBoxColliderComponent->setSize(40, 680);
	sf::Vector2f boxSize = lightning->mBoxColliderComponent->getCollisionBox()->getSize();
	//lightning->mBoxColliderComponent->setOrigin(sf::Vector2f(boxSize.x,boxSize.y));
	
	
	//lightning->mBoxColliderComponent->setVisible(true);
	lightning->setPosition(70,0);
}

void RyobeLogic::update(Grid& grid)
{
	updateDirection();

	mVelocity.x = 0;
	
	if(mGameObject->mState->getName() == "CStateRyobeAttacking")
	{
		CStateRyobeAttacking* attackState = dynamic_cast<CStateRyobeAttacking*>(mGameObject->mState);
		if(attackState->attackType == Attacks::RYOBE_EMBRACER)
			mIsUntouchable = true;
		else
			mIsUntouchable = false;
	}
	
	lightning->mRenderComponent->runSpriteAnim(*lightning);

	
	
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

	sf::IntRect rect = mHealthBar->getSprite()->getTextureRect();
	rect.width = mMaxRectWidth * (mHealth * 0.01);
	mHealthBar->getSprite()->setTextureRect(rect);

	mHealthBar->getSprite()->setSize(sf::Vector2f(mMaxBarWidth * (mHealth * 0.01), mHealthBarHeight));
	
	float healthBarDiff = (mHealthBarWidth* (damageAmount * 0.01) );
	mHealthBar->move(mMaxBarWidth * (damageAmount * 0.01), 0);

	/*float barSize = mHealthBar->mRenderComponent->mSprite.getSize().x;
	
	if(mHealth <= 0)
	{
		mHealthBar->mRenderComponent->mSprite.setSize(sf::Vector2f(0,mHealthBarHeight));
	}
	else
	{
		mHealthBar->mRenderComponent->mSprite.setSize(sf::Vector2f(barSize - healthBarDiff,mHealthBarHeight));

	}

	sf::IntRect rect = mHealthBar->mRenderComponent->mSprite.getTextureRect();
	rect.width -= healthBarDiff;
	mHealthBar->mRenderComponent->mSprite.setTextureRect(rect);
	*/

	//mHealthBar->move(healthBarDiff, 0);

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