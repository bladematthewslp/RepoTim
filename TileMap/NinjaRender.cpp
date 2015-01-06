#include "NinjaRender.h"
#include "GameObject.h"

NinjaRender::NinjaRender(GameObject* mGameObject) 
	: RenderComponent(mGameObject)
{
	mImage.loadFromFile("Sprites/ninja_spritesheet.png");
	mImage.createMaskFromColor(sf::Color(34,177,76), 1);

	mTexture.loadFromImage(mImage);//loadFromFile("ninja_spritesheet.png");
	mSprite.setSize(sf::Vector2f(400,400));
	mSprite.setTexture(&mTexture);
	mSprite.setTextureRect(sf::IntRect(0,0, 200, 200));
	mSprite.setOrigin(mSprite.getLocalBounds().width/2, mSprite.getLocalBounds().height/2);

	createSpriteAnim(sf::IntRect(200,0,200,200),"Standing",true,7, 3,7);
	createSpriteAnim(sf::IntRect(200,200,200,200),"Running",true,8, 1.5);//, 3,7);
	setAnimation("Running");
}

void NinjaRender::update()
{
	
	RenderComponent::update();
}