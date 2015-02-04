#include "PlayerRender.h"
#include <iostream>

PlayerRender::PlayerRender(GameObject* mGameObject) : RenderComponent(mGameObject)
{
	mSprite.setSize(sf::Vector2f(400, 400));
	mSprite.setOrigin(mSprite.getLocalBounds().width/2, mSprite.getLocalBounds().height/2);
	
	//mPlayerImage.loadFromFile("Sprites/player_spritesheet.png");
	
	mPlayerImage = mImageHolder.get(Images::Player);
	mPlayerImage.createMaskFromColor(sf::Color(0,128,0), 1);
	mPlayerTexture.loadFromImage(mPlayerImage);
	
	//mSprite.setOutlineColor(sf::Color::Yellow);
	//mSprite.setOutlineThickness(2);
	mSprite.setTexture(&mPlayerTexture);
	//mSprite.setTextureRect(sf::IntRect(0,0, 200,200));

	// Basic
	createSpriteAnim(sf::IntRect(200,0,200,200),"Standing", false, 1,1,0);
	createSpriteAnim(sf::IntRect(200,200,200,200), "Running", true,8);
	createSpriteAnim(sf::IntRect(200,400,200,200), "Guarding", false, 1);
	createSpriteAnim(sf::IntRect(200,400,200,200), "Blocking", false,1,1,1,1);

	// Air Basic
	createSpriteAnim(sf::IntRect(200,600,200,200), "Jumping", true, 3, 1,4,1);
	createSpriteAnim(sf::IntRect(200,600,200,200), "Falling", true, 6,1,-1,4);

	// Ground Attacks
	createSpriteAnim(sf::IntRect(200,800,200,200), "Slash1", false, 7,.9, 4);
	createSpriteAnim(sf::IntRect(200,1000,200,200), "Slash2Part1", false, 4,.9, 3);
	createSpriteAnim(sf::IntRect(200,1000,200,200), "Slash2Part2", false, 7,1, 3,4);
	createSpriteAnim(sf::IntRect(200,1200,200,200), "Slash3", false, 7,.9, 5);
	createSpriteAnim(sf::IntRect(200,3000,200,200), "Stinger", false, 8,1);
	createSpriteAnim(sf::IntRect(200,3000,200,200), "QuickStinger", false, 6,.9,5,2);
	createSpriteAnim(sf::IntRect(200,3200,200,200), "Uprising", false, 8);
	createSpriteAnim(sf::IntRect(200,3200,200,200), "QuickUprising", false, 7,.9,-1,2);
	createSpriteAnim(sf::IntRect(200,2000,200,200), "PLAYER_IMPACT", false,7, 1);
	createSpriteAnim(sf::IntRect(200,2000,200,200), "PLAYER_IMPACT_REPEATED", true, 7, 1,-1, 5);
	createSpriteAnim(sf::IntRect(200,2000,200,200), "PLAYER_IMPACT_RECOVERING", false, 9, 1, -1, 7);
	createSpriteAnim(sf::IntRect(200,2800,200,200), "PLAYER_CHOPPERSTYLE", false, 9);//9, 1, -1, 7);
	createSpriteAnim(sf::IntRect(200,2800,200,200), "PLAYER_CHOPPERSTYLE_REPEATED", true, 9,1, -1,7);//9, 1, -1, 7);
	createSpriteAnim(sf::IntRect(200,2800,200,200), "PLAYER_CHOPPERSTYLE_RECOVERING", false, 12,1, -1,9);//9, 1, -1, 7);

	// Air Attacks
	createSpriteAnim(sf::IntRect(200,2200,200,200), "PLAYER_SWEEP", false, 5, 1.1,4);
	createSpriteAnim(sf::IntRect(200,2600,200,200), "PLAYER_REPEL", false, 9, 1.1);
	

	// Hit Ground
	createSpriteAnim(sf::IntRect(200,1400,200,200), "Hit", false,5, 1.8f);
	createSpriteAnim(sf::IntRect(200,1800,200,200), "HitRecover", false, 4, 2.2f);
	
	// Hit Air
	createSpriteAnim(sf::IntRect(200,2400,200,200), "HitAirPart1", false,1);
	createSpriteAnim(sf::IntRect(200,2400,200,200), "HitAirPart2", false,5,1,-1, 1);

	// Dead Ground
	createSpriteAnim(sf::IntRect(200,1600,200,200), "Knockout", false, 9, 1.7f);
	
	// Dead Air
	createSpriteAnim(sf::IntRect(200,1600,200,200), "KnockoutAirPart1", true, 4, 1.7f);
	createSpriteAnim(sf::IntRect(200,1600,200,200), "KnockoutAirPart2", false,9,1.7,-1,5);//, 1.7f);

}


void PlayerRender::update(sf::RenderTarget& window)
{
	
	
	RenderComponent::update(window);
	


}
