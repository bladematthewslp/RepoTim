#include "PlayerRender.h"
#include <iostream>

PlayerRender::PlayerRender(GameObject* mGameObject) : RenderComponent(mGameObject)
{
	mSprite.setSize(sf::Vector2f(400, 400));
	mSprite.setOrigin(mSprite.getLocalBounds().width/2, mSprite.getLocalBounds().height/2);
	
	mPlayerImage.loadFromFile("Sprites/SpriteSheet_new.png");
	mPlayerImage.createMaskFromColor(sf::Color(0,128,0), 1);
	mPlayerTexture.loadFromImage(mPlayerImage);
	//mSprite.setOutlineColor(sf::Color::Yellow);
	//mSprite.setOutlineThickness(2);
	mSprite.setTexture(&mPlayerTexture);
	//mSprite.setTextureRect(sf::IntRect(0,0, 200,200));

	createSpriteAnim(sf::IntRect(200,0,200,200),"Standing", false, 1,1);
	createSpriteAnim(sf::IntRect(200,200,200,200), "Running", true,8);
	createSpriteAnim(sf::IntRect(200,400,200,200), "Guarding", false, 1);
	createSpriteAnim(sf::IntRect(200,400,200,200), "Blocking", false,1,1,1,1);
	createSpriteAnim(sf::IntRect(200,600,200,200), "Jumping", true, 3, 1,4,1);
	createSpriteAnim(sf::IntRect(200,600,200,200), "Falling", true, 6,1,-1,4);
	createSpriteAnim(sf::IntRect(200,800,200,200), "Slash1", false, 7,1, 4);
	createSpriteAnim(sf::IntRect(200,1000,200,200), "Slash2", false, 6,1, 3);
	createSpriteAnim(sf::IntRect(200,1200,200,200), "Slash3", false, 7,1, 5);
	
}


void PlayerRender::update()
{
	
	
	RenderComponent::update();
	


}
