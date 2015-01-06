
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <iostream>

RenderComponent::RenderComponent(GameObject* gameObject)
	: Component(gameObject)
	,mSprite()
	, mTexture()
	, currentAnim("")
	, mImage()
{
	//std::cout << "CREATING RENDER COMPONENT " << std::endl;
	//mGameObject = gameObject;

}

void RenderComponent::createSpriteAnim(sf::IntRect rect, std::string animName, bool loop, int numFrames,float speed, int frameToHold, int startingFrame )
{
	
	SpriteAnim* anim = std::unique_ptr<SpriteAnim>(new SpriteAnim(rect,numFrames, frameToHold, loop, speed, startingFrame)).release();
	mSpriteSet.insert(std::make_pair(animName, anim));

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
	
	currentAnim = animName;
}

int RenderComponent::runSpriteAnim(GameObject& gameObject)
{
	/*if(currentAnim != animName && currentAnim != "")
		stopSpriteAnim();

	currentAnim = animName;*/
	
	return mSpriteSet.find(currentAnim)->second->run(gameObject);
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

void RenderComponent::update()
{
	mSprite.setPosition(mGameObject->getPosition());
}

void RenderComponent::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const
{
	/*if(this->mIsEnabled == true)
		target.draw(mSprite);*/

}

void RenderComponent::render(sf::RenderWindow& window)
{
	if(this->mIsEnabled == true)
		window.draw(mSprite);

}