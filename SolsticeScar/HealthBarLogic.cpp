#include "HealthBarLogic.h"

HealthBarLogic::HealthBarLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
{
	mGameObject->getSprite()->setTexture(&mGameObject->mRenderComponent->mTextureHolder.get(Textures::PlayerHUDHealthbar));


	maxBarWidth = mGameObject->getSprite()->getSize().x;
	maxRectWidth = mGameObject->getSprite()->getTextureRect().width;

	healthBarHeight = mGameObject->getSprite()->getSize().y;

}

void HealthBarLogic::updateHealth(int health)
{
	sf::IntRect rect = mGameObject->getSprite()->getTextureRect();
	rect.width = maxRectWidth * (health * 0.01);
	mGameObject->getSprite()->setTextureRect(rect);

	mGameObject->getSprite()->setSize(sf::Vector2f(maxBarWidth * (health * 0.01), healthBarHeight));
	

}