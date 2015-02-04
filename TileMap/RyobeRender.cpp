#include "RyobeRender.h"



RyobeRender::RyobeRender(GameObject* gameObject)
	: RenderComponent(gameObject)
{
	mImage = mImageHolder.get(Images::Ryobe);
	
	mTexture.loadFromImage(mImage);
	mSprite.setTexture(&mTexture);
	mSprite.setSize(sf::Vector2f(325,325));
	mSprite.setTextureRect(sf::IntRect(0,0,200,200));
	mSprite.setOrigin(mSprite.getLocalBounds().width/2, mSprite.getLocalBounds().height/2);
	mSprite.setScale(-1,1);
	createSpriteAnim(sf::IntRect(200,0,200,200), "Standing", true,5,5,-1,1);


}