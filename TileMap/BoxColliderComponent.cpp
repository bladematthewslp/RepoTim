#include "BoxColliderComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "System.h"
#include "PlayerLogic.h"
#include <iostream>

BoxColliderComponent::BoxColliderComponent(GameObject* gameObject) : Component(gameObject), mIsVisible(true)
{

	if(gameObject->mRenderComponent != nullptr)
	{
		sf::Vector2f spriteSize = gameObject->getSprite()->getSize();
		//mCollisionBox.setSize(sf::Vector2f(80,100));
		mCollisionBox.setSize(spriteSize);
		
	}
	else
	{
		mCollisionBox.setSize(sf::Vector2f(50,50));
		
	}

	mCollisionBox.setFillColor(sf::Color::Transparent);
	mCollisionBox.setOutlineColor(sf::Color::Cyan);
	mCollisionBox.setOutlineThickness(2);
	
	mCollisionBox.setOrigin(mCollisionBox.getSize().x/2, mCollisionBox.getSize().y/2);
	
	player = System::findGameObjectByName("Player");
}

void BoxColliderComponent::setSize(float x, float y)
{
	mCollisionBox.setSize(sf::Vector2f(x,y));
	mCollisionBox.setOrigin(mCollisionBox.getSize().x/2, mCollisionBox.getSize().y/2);
}

void BoxColliderComponent::update()
{

	
	mCollisionBox.setPosition(mGameObject->getPosition());

	//std::cout << mCollisionBox.getPosition().x << std::endl;

	//sf::Vector2f boxPosition(mGameObject->getSprite()->getGlobalBounds().left + mGameObject->getSprite()->getGlobalBounds().width,
	//						 mGameObject->getSprite()->getGlobalBounds().top + mGameObject->getSprite()->getGlobalBounds().height);
	
	
	//mCollisionBox.setPosition(mGameObject->getPosition() + sf::Vector2f(mGameObject->getSprite()->getOrigin().x /1.5, mGameObject->getSprite()->getOrigin().y /1.5));


	
	//mCollisionBox.setSize(sf::Vector2f(80,100));
	
	PlayerLogic* playerLogic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	/*if(playerLogic->box.intersects(collisionBox))
	{
		std::cout << collisionBox.left << std::endl;
	}
	sf::RectangleShape rr(sf::Vector2f(50,59));*/

	
}

void BoxColliderComponent::render(sf::RenderWindow& window)
{
	if(this->mIsVisible)
		window.draw(mCollisionBox);
	//std::cout << "Rendering BOX COLLIDER COMPONENT" << std::endl;
}