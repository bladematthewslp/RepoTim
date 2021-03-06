
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "System.h"
#include <iostream>

ImageHolder RenderComponent::mImageHolder;
TextureHolder RenderComponent::mTextureHolder;

void RenderComponent::loadImages()
{
	mImageHolder.load(Images::BloodAnimationA, "Sprites/blood_animation_A.png");
	mImageHolder.load(Images::Player,		"Sprites/player_spritesheet.png");
	mImageHolder.load(Images::Ninja,		"Sprites/ninja_spritesheet.png");
	mImageHolder.load(Images::Ryobe,		"Sprites/ryobe_spritesheet.png");
	//mImageHolder.load(Images::RyobeDagger,	"Sprites/dagger.png");

	mTextureHolder.load(Textures::BloodAnimationA, "Sprites/blood_animation_A.png");
	mTextureHolder.load(Textures::GridBlockCrate, "Sprites/crate.png");
	mTextureHolder.load(Textures::GreenOrb,		"Sprites/green_orb.png");
	mTextureHolder.load(Textures::LightningWall, "Sprites/lightning.png");
	mTextureHolder.load(Textures::PlayerHUD,	"Sprites/HUD/DojiHUDNoHealthbar.png");
	mTextureHolder.load(Textures::PlayerHUDHealthbar,"Sprites/HUD/DojiHealthbar.png");
	mTextureHolder.load(Textures::RedOrb,		"Sprites/red_orb.png");
	mTextureHolder.load(Textures::RyobeDagger,		"Sprites/dagger.png");
	mTextureHolder.load(Textures::RyobeHUD,		"Sprites/HUD/RyobiHUDNoHealthbar.png");
	mTextureHolder.load(Textures::RyobeHUDHealthbar,"Sprites/HUD/RyobiHealthbar.png");
	mTextureHolder.load(Textures::RyobeParryEffect, "Sprites/electricParry.png");
	mTextureHolder.load(Textures::WoodsBackground,"Sprites/Background/woods_background.png");
	mTextureHolder.load(Textures::WoodsForeground,"Sprites/Background/woods_foreground.png");
	mTextureHolder.load(Textures::WoodsBackgroundComplete,"Sprites/Background/woods_background_complete.png");
}

void RenderComponent::unloadImages()
{
	mImageHolder.mResourceMap.clear();
	mTextureHolder.mResourceMap.clear();
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

RenderComponent::~RenderComponent()
{
	std::vector<RenderComponent*>::iterator ren_itr;
	ren_itr = std::remove(System::mRenderComponents.begin(), System::mRenderComponents.end(), this);
	System::mRenderComponents.erase(ren_itr, System::mRenderComponents.end());

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
	auto sprite = mSpriteSet.find(currentAnim);//->second->run(gameObject);
	if(sprite == mSpriteSet.end())
	{
		std::cout << "Sprite " << currentAnim << " not found. Not playing sprite " << std::endl;
		return SpriteAnim::Status::FAILURE;
	}
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