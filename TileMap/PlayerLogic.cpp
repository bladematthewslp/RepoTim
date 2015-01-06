#include "PlayerLogic.h"
#include "PlayerState.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "StandingState.h"
#include <iostream>

const sf::Time deltaTime = sf::seconds(1.0f/60.0f);
PlayerLogic::PlayerLogic(GameObject* mGameObject)
	: LogicComponent(mGameObject)
	, mDirection(Direction::Right)
	, box(mGameObject->getPosition().x - 50, mGameObject->getPosition().y, 100, 100)
{
	mGameObject->setPosition(300,(32*16) - mGameObject->getSprite()->getLocalBounds().height/8);

	//box = mGameObject->getPosition().x - 50, mGameObject->getPosition().y, 100, 100
	GameObjectDesc boxDesc("playerBBox", 
							sf::RectangleShape(sf::Vector2f(mGameObject->getSprite()->getGlobalBounds().width/4,mGameObject->getSprite()->getGlobalBounds().height/4)), 
							Layer::Default,
							ComponentType::RenderComponent);
	playerBBox = std::unique_ptr<GameObject>
	(new GameObject(boxDesc)).release();//sf::RectangleShape(sf::Vector2f(mGameObject->getSprite()->getGlobalBounds().width/4,mGameObject->getSprite()->getGlobalBounds().height/4)),ComponentType::RenderComponent,"playerBBox")).release();
	playerBBox->getSprite()->setOrigin(playerBBox->getSprite()->getLocalBounds().width/2, playerBBox->getSprite()->getLocalBounds().height/2);
	mGameObject->addChild(playerBBox);
	playerBBox->getRenderComponent()->mSprite.setFillColor(sf::Color::Transparent);
	
	
	playerObject = mGameObject;
	mGameObject->mState = std::unique_ptr<StandingState>(new StandingState(mGameObject)).release();
	//mGameObject->mState->entry();
}

void PlayerLogic::update(Grid& grid)
{
	updateBox();

	//std::cout << mGameObject->getPosition().x << std::endl;
	PlayerState* state = mGameObject->mState->update(playerObject, deltaTime, grid);
	if(state != mGameObject->mState)
	{
		mGameObject->mState = state;
	}
}

sf::Vector2f PlayerLogic::getPosition() const
{
	return this->mGameObject->getPosition();
}

void PlayerLogic::setPosition(sf::Vector2f pos)
{
	this->mGameObject->setPosition(pos);
}

sf::FloatRect PlayerLogic::getLocalBounds() const 
{ 
	return this->mGameObject->getSprite()->getLocalBounds(); 
};
sf::FloatRect PlayerLogic::getGlobalBounds() const 
{ 
	return this->mGameObject->getSprite()->getGlobalBounds(); 
};

sf::Vector2f PlayerLogic::getVelocity()
{
	return mVelocity;		
};

void PlayerLogic::setVelocity(sf::Vector2f vel)
{
	mVelocity = vel;
};

void PlayerLogic::setVelocityX(float x)
{
	mVelocity.x = x;	
};

void PlayerLogic::setVelocityY(float y)
{
	mVelocity.y = y;
}

void PlayerLogic::move(sf::Vector2f dir)
{
	mGameObject->move(dir);
	updateBox();
};
void PlayerLogic::move(float x, float y)
{
	mGameObject->move(x,y);		
	updateBox();
};

int PlayerLogic::getDirection()
{
	return mDirection;
}

void PlayerLogic::updateDirection(int dir)
{
	sf::RectangleShape* sprite = mGameObject->getSprite();
	if(mDirection != dir)
	{
		mDirection = dir;
		sprite->setScale(-sprite->getScale().x, sprite->getScale().y);
	}
	
}

float PlayerLogic::getRunningSpeed()
{
	return 5.0f;

}

void PlayerLogic::updateBox()
{
	box.left = mGameObject->getPosition().x - 40;
	box.top = mGameObject->getPosition().y - 50;
	box.width = 80;
	box.height = 100;
}