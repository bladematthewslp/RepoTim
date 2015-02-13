#include "DaggerLogic.h"
#include "RyobeLogic.h"

DaggerLogic::DaggerLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
{
	GameObject* ryobe = System::findGameObjectByName("Ryobe");
	
	int dir = dynamic_cast<RyobeLogic*>(ryobe->mLogicComponent)->getDirection();
	speed = dir * 5;

	mDirection = dir;
	gameObject->mRenderComponent->mImage = RenderComponent::mImageHolder.get(Images::RyobeDagger);									
	gameObject->mRenderComponent->mTexture.loadFromImage(gameObject->mRenderComponent->mImage);										
	gameObject->mRenderComponent->mSprite.setTexture(&gameObject->mRenderComponent->mTexture);	
	sf::RectangleShape* sprite = mGameObject->getSprite();
	sprite->setScale(-sprite->getScale().x * dir, sprite->getScale().y);
	gameObject->addComponent(ComponentType::BoxColliderComponent);																	
	gameObject->mBoxColliderComponent->setSize(40,5);

	if(dir == Direction::Left)
		gameObject->mBoxColliderComponent->setOrigin(sprite->getOrigin());
	else
		gameObject->mBoxColliderComponent->setOrigin(sf::Vector2f(40,0));

	//gameObject->mBoxColliderComponent->setOrigin(sf::Vector2f(gameObject->mBoxColliderComponent->getCollisionBox()->getSize().x/8, gameObject->mBoxColliderComponent->getCollisionBox()->getSize().y/8));
	gameObject->mBoxColliderComponent->setVisible(true);	
	

	
}

void DaggerLogic::update(Grid& grid)
{
	
	mGameObject->move(speed, 0);

}


int DaggerLogic::getDirection()
{
	return mDirection;
}