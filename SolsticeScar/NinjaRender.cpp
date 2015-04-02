#include "NinjaRender.h"
#include "GameObject.h"

NinjaRender::NinjaRender(GameObject* mGameObject) 
	: RenderComponent(mGameObject)
{
	mImage = mImageHolder.get(Images::Ninja);
	
	mImage.createMaskFromColor(sf::Color(34,177,76), 1);

	mTexture.loadFromImage(mImage);//loadFromFile("ninja_spritesheet.png");
	mSprite.setSize(sf::Vector2f(400,400));
	mSprite.setTexture(&mTexture);
	
	mSprite.setTextureRect(sf::IntRect(0,0, 200, 200));
	mSprite.setOrigin(mSprite.getLocalBounds().width/2, mSprite.getLocalBounds().height/2);
	
	// Basic
	createSpriteAnim(sf::IntRect(200,0,200,200),"Standing",true,7, 3,7);
	createSpriteAnim(sf::IntRect(200,200,200,200),"Running",true,8, 1.5);//, 3,7);

	// Air
	createSpriteAnim(sf::IntRect(200,1600,200,200),"Falling",true,2, 1.5);//, 3,7);
	
	// Attacks
	createSpriteAnim(sf::IntRect(200,400,200,200), Attacks::NINJA_SLASH_GROUND,false, 15, 1);

	// Hits
	createSpriteAnim(sf::IntRect(200,1000,200,200),"Hit", true,2,3);
	createSpriteAnim(sf::IntRect(200,1200,200,200),"Hit2", true,2,3);

	createSpriteAnim(sf::IntRect(200,800,200,200),"DraggedByExpel", false, 12, 1.5, -1, 1);

	createSpriteAnim(sf::IntRect(200,600,200,200),"AirHit1",false, 1,1,-1,4);
	createSpriteAnim(sf::IntRect(200,1000,200,200),"AirHit2",false, 1,1,-1,1);

	createSpriteAnim(sf::IntRect(200,1400,200,200),"AirHitToGround1",true, 3, 1.5,-1,1);
	createSpriteAnim(sf::IntRect(200,1400,200,200),"AirHitToGround2",false, 5, 1.5,-1,3);

	createSpriteAnim(sf::IntRect(200,600,200,200),"Dying",false, 12, 1.5);// 15, 2);
	
	createSpriteAnim(sf::IntRect(200,800,200,200),"DeadAirPart1",false,5);// 1,1,-1,1);
	createSpriteAnim(sf::IntRect(200,800,200,200),"DeadAirPart2",false, 10,1,-1,5);

	createSpriteAnim(sf::IntRect(200,1800,200,200),"DieShredded",false, 10,1,-1);

	createSpriteAnim(sf::IntRect(200,800,200,200),"HitAndDie",false, 10, 1.5);
	createSpriteAnim(sf::IntRect(200,1400,200,200),"LayToStand",true, 9, 2.1,-1,6);
	
}

void NinjaRender::update(sf::RenderTarget& window)
{
	
	RenderComponent::update(window);
}