
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "System.h"
#include <iostream>

ImageHolder RenderComponent::mImageHolder;
TextureHolder RenderComponent::mTextureHolder;

void RenderComponent::loadImages()
{
	mImageHolder.load(Images::Player, "Sprites/player_spritesheet.png");
	mImageHolder.load(Images::Ninja, "Sprites/ninja_spritesheet.png");
	mImageHolder.load(Images::RedOrb, "Sprites/red_orb.png");
	mImageHolder.load(Images::GreenOrb, "Sprites/green_orb.png");
	mImageHolder.load(Images::Ryobe,	"Sprites/ryobe_spritesheet.png");
	//mImageHolder.load(Images::HealthBar100, "Sprites/healthbar/100.png");

	mTextureHolder.load(Textures::HealthBar100, "Sprites/healthbar/100.png");
	mTextureHolder.load(Textures::HealthBar90, "Sprites/healthbar/90.png");
	mTextureHolder.load(Textures::HealthBar80, "Sprites/healthbar/80.png");
	mTextureHolder.load(Textures::HealthBar70, "Sprites/healthbar/70.png");
	mTextureHolder.load(Textures::HealthBar60, "Sprites/healthbar/60.png");
	mTextureHolder.load(Textures::HealthBar50, "Sprites/healthbar/50.png");
	mTextureHolder.load(Textures::HealthBar40, "Sprites/healthbar/40.png");
	mTextureHolder.load(Textures::HealthBar30, "Sprites/healthbar/30.png");
	mTextureHolder.load(Textures::HealthBar20, "Sprites/healthbar/20.png");
	mTextureHolder.load(Textures::HealthBar10, "Sprites/healthbar/10.png");
	mTextureHolder.load(Textures::HealthBar0,	"Sprites/healthbar/0.png");
	mTextureHolder.load(Textures::Mugshot,		"Sprites/mugshot.png");
}




RenderComponent::RenderComponent(GameObject* gameObject)
	: Component(gameObject)
	, mSprite()
	, mTexture()
	, currentAnim("")
	, mImage()
{
	mAnimStatus = SpriteAnim::Status::FAILURE;
	//std::cout << "CREATING RENDER COMPONENT " << std::endl;
	//mGameObject = gameObject;
	System::addComponent(this);
}

void RenderComponent::createSpriteAnim(sf::IntRect rect, std::string animName, bool loop, int numFrames,float speed, int frameToHold, int startingFrame )
{
	
	SpriteAnim* anim = std::unique_ptr<SpriteAnim>(new SpriteAnim(rect,numFrames, frameToHold, loop, speed, startingFrame)).release();
	mSpriteSet.insert(std::make_pair(animName, anim));

}

bool RenderComponent::getAnimStatus()
{
	return mAnimStatus;

}
bool RenderComponent::isAnimDelayed()
{
	auto found = mSpriteSet.find(currentAnim);///->second-isAnimDelayed()
	
	if(found != mSpriteSet.end() )
		return found->second->isAnimDelayed();
	else 
		return false;
}

void RenderComponent::setAnimation(std::string animName)
{
	if(currentAnim != animName && currentAnim != "")
		stopSpriteAnim();
	
	mAnimStatus = SpriteAnim::Status::RESTARTED;
	currentAnim = animName;
}

int RenderComponent::runSpriteAnim(GameObject& gameObject)
{
	/*if(currentAnim != animName && currentAnim != "")
		stopSpriteAnim();

	currentAnim = animName;*/
	mAnimStatus = mSpriteSet.find(currentAnim)->second->run(gameObject);
	return mAnimStatus;
}

void RenderComponent::stopSpriteAnim()
{
	mSpriteSet.find(currentAnim)->second->exit();
}

void RenderComponent::setFillColor(sf::Color color)
{
	mSprite.setFillColor(color);
}

void RenderComponent::Awake()
{
}
void RenderComponent::Destroy()
{
}
void RenderComponent::FixedUpdate()
{
}

void RenderComponent::LateUpdate()
{
}
void RenderComponent::Start()
{
	
}

void RenderComponent::update(sf::RenderTarget& window)
{
	if(mGameObject->mLayerName == Layer::UI)
	{
		int xOffset = window.getView().getCenter().x - window.getView().getSize().x/2;
		mSprite.setPosition(mGameObject->getPosition().x + xOffset, mGameObject->getPosition().y);
	}
	else
	{
		mSprite.setPosition(mGameObject->getPosition());
	}
}

void RenderComponent::draw(sf::RenderTarget& window, sf::RenderStates states ) const
{
	if(this->mIsEnabled == true)
	{
		window.draw(mSprite);
	}
}

void RenderComponent::render(sf::RenderWindow& window)
{
	// trying to use draw() more often instead of render()
	//std::cout << "RENDER COMPONENT :: RENDER " << std::endl;
	/*
	if(this->mIsEnabled == true)
		window.draw(mSprite);
		*/
}