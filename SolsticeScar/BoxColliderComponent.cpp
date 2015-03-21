#include "BoxColliderComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "System.h"
#include "PlayerLogic.h"
#include "StandingState.h"
#include "FallingState.h"
#include <iostream>
#include "Grid.h"
#include "Foreach.hpp"

BoxColliderComponent::BoxColliderComponent(GameObject* gameObject) 
	: Component(gameObject)
	, mIsVisible(false)
	, mOccupiedCells()
	, mDeleted(false)
{
	
	// 1.) Set size of collision box to size of sprite, if render component is present, if not set to default 50,50
	if(gameObject->mRenderComponent != nullptr)
	{
		sf::Vector2f spriteSize = gameObject->getSprite()->getSize();
		mCollisionBox.setSize(spriteSize);
	}
	else
	{
		mCollisionBox.setSize(sf::Vector2f(50,50));
	}
	
	// 2.) Set collision box parameters to transparent color and thin cyan outline
	mCollisionBox.setFillColor(sf::Color::Transparent);
	mCollisionBox.setOutlineColor(sf::Color::Cyan);
	mCollisionBox.setOutlineThickness(1);
	
	// 3.) Center the collision box
	//mCollisionBox.setOrigin(mCollisionBox.getSize().x/2, mCollisionBox.getSize().y/2);
	
	System::addComponent(this);
}

BoxColliderComponent::~BoxColliderComponent()
{
	mDeleted = true;
	std::vector<BoxColliderComponent*>::iterator box_itr;
	box_itr = std::remove(System::mBoxColliderComponents.begin(), System::mBoxColliderComponents.end(), this);
	System::mBoxColliderComponents.erase(box_itr, System::mBoxColliderComponents.end());


}

void BoxColliderComponent::onCollisionEnter(Grid& grid, BoxColliderComponent* other)
{
	
	//mCollidedObjects.insert(other);
	
	//std::cout << mGameObject->mName << "," << other->mGameObject->mName << std::endl;

	/*for(std::set<BoxColliderComponent*>::iterator iter = mCollidedObjects.begin(); iter != mCollidedObjects.end();
		iter ++)
	{
		std::cout << (*iter)->mGameObject->mName << std::endl;
	}
	std::cout << "fin" << std::endl;*/
}

void BoxColliderComponent::onCollisionStay(Grid& grid, BoxColliderComponent* other)
{
	/*
	for(std::set<BoxColliderComponent*>::iterator box_itr = mColliders.begin(); box_itr != mColliders.end(); ++box_itr)
	{
		if( (*box_itr) == other)
		{
			mColliders.erase(box_itr, mColliders.end());
			break;
		}
	}*/
}
BoxColliderComponent* BoxColliderComponent::onCollisionExit(Grid& grid, BoxColliderComponent* other)
{
	/*
	for(std::set<BoxColliderComponent*>::iterator iter = mCollidedObjects.begin(); 
		iter != mCollidedObjects.end();
		++iter )
	{
		/*
		bool exists = false;
		FOREACH(auto col, System::mBoxColliderComponents)
		{
			if(col == (*iter))
			{
				exists = true;
				break;
			}
		}
		if(exists == false)
		{
			mCollidedObjects.erase(*iter);
			continue;
		}
		//
		if(!mCollisionBox.getGlobalBounds().intersects((*iter)->getCollisionBox()->getGlobalBounds()))
		{
			BoxColliderComponent* object = (*iter);
			mCollidedObjects.erase(*iter);
			return object;
		}
		if(mCollidedObjects.size() == 0)
			break;
	}*/
	return nullptr;
}

void BoxColliderComponent::setSize(float x, float y)
{
	mCollisionBox.setSize(sf::Vector2f(x,y));
	mCollisionBox.setOrigin(mCollisionBox.getSize().x/2, mCollisionBox.getSize().y/2);
}

void BoxColliderComponent::setOrigin(sf::Vector2f origin)
{
	mCollisionBox.setOrigin(origin.x, origin.y);
}

void BoxColliderComponent::update()
{
	// update the collision box to match the game object's position
	if(mGameObject == nullptr)
		return;

	mCollisionBox.setPosition(mGameObject->getPosition());
}

void BoxColliderComponent::render(sf::RenderWindow& window)
{
	if(this->mIsEnabled == true && this->mIsVisible)
		window.draw(mCollisionBox);
}

void BoxColliderComponent::setVisible(bool isVisible)
{
	mIsVisible = isVisible;
}

sf::RectangleShape* BoxColliderComponent::getCollisionBox()
{

	return &mCollisionBox;

}



std::vector<std::array<int, 2>> BoxColliderComponent::getOccupiedCells()
{
	
	return mOccupiedCells;
}