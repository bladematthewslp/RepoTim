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
	createSpriteAnim(sf::IntRect(200,200,200,200), "Walking", true,4,2.9,-1,1);
	createSpriteAnim(sf::IntRect(200,400,200,200), "SwordAttack1", true,8,1,5,1);
	createSpriteAnim(sf::IntRect(200,600,200,200), "Punch1", true,6,3,3);
	createSpriteAnim(sf::IntRect(200,800,200,200), "Punch2", true,3,3,2);
	createSpriteAnim(sf::IntRect(200,1000,200,200), "Charge", true,3,1, -1, 1);
	createSpriteAnim(sf::IntRect(200,1200,200,200), "Teleport", false,9,1.3);
	createSpriteAnim(sf::IntRect(200,400, 200, 200),"Blocking", false, 1, 1,-1, 6);
}