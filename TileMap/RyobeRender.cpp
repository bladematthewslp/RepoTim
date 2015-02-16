#include "RyobeRender.h"



RyobeRender::RyobeRender(GameObject* gameObject)
	: RenderComponent(gameObject)
{
	mImage = mImageHolder.get(Images::Ryobe);
	
	mTexture.loadFromImage(mImage);
	mSprite.setTexture(&mTexture);
	mSprite.setSize(sf::Vector2f(325,325));
	mSprite.setTextureRect(sf::IntRect(0,0,200,200));
	mTexture.setSmooth(true);
	mSprite.setOrigin(mSprite.getLocalBounds().width/2, mSprite.getLocalBounds().height/2);
	mSprite.setScale(-1,1);
	createSpriteAnim(sf::IntRect(200,0,200,200), "Standing", true,5,5,-1,1);
	createSpriteAnim(sf::IntRect(200,200,200,200), "Walking", true,4,2.9,-1,1);
	createSpriteAnim(sf::IntRect(200,400,200,200), "TeleportSwordAttack1", false,8,1,0);
	createSpriteAnim(sf::IntRect(200,400,200,200), "SwordAttack1", false,8,2,5,1);
	createSpriteAnim(sf::IntRect(200,1400,200,200), "WeaponThrow", false,4,3.8);

	createSpriteAnim(sf::IntRect(200,800,200,200), "AttackReady", true,1,10);
	createSpriteAnim(sf::IntRect(200,600,200,200), "Punch1", true,6,3,1);
	createSpriteAnim(sf::IntRect(200,800,200,200), "Punch2", true,5,3,0);
	createSpriteAnim(sf::IntRect(200,1000,200,200), "Charge", true,3,1, -1, 1);
	createSpriteAnim(sf::IntRect(200,1200,200,200), "Teleport", false,9,1.3);
	createSpriteAnim(sf::IntRect(200,400, 200, 200),"Blocking", false, 1, 1,-1, 6);
	createSpriteAnim(sf::IntRect(200,1600, 200, 200),"Charge2", true, 4, 1.5);
	createSpriteAnim(sf::IntRect(200,1800, 200, 200),"EmbracerPart1", false, 5, 1.5);
	createSpriteAnim(sf::IntRect(200,2000, 200, 200),"EmbracerPart2", false, 9, 4.5);
	//createSpriteAnim(sf::IntRect(200,1800, 200, 200),"EmbracerPart3", false, 9, 4.5, -1,5);


}