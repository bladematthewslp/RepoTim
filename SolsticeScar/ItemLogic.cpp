#include "ItemLogic.h"

ItemLogic::ItemLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
	, mVelocity(0, -0.8f)
	, acceleration(-0.01f)
{
	timer = 0;


}

void ItemLogic::update(Grid& grid)
{
	timer += 1;
	if(timer == 60)
	{
		mGameObject->mBoxColliderComponent = std::unique_ptr<BoxColliderComponent>(new BoxColliderComponent(mGameObject)).release();
		/*sf::Vector2f size = mGameObject->getSprite()->getSize();
		mGameObject->mBoxColliderComponent->setSize(size.x, size.y);
		mGameObject->mBoxColliderComponent->setOrigin(mGameObject->getPosition());*/
		//mGameObject->mBoxColliderComponent->setVisible(true);
	}

	if(mGameObject->mBoxColliderComponent != nullptr)
	{

		mVelocity.y += acceleration;
		if(acceleration < 0)				// if acceleration is upward
		{
			if(mVelocity.y < -.5)
			{
				acceleration *= -1;
				mVelocity.y += acceleration;
			}
		}
		else if(acceleration > 0)		// if acceleration is downward
		{
			if(grid.checkCollisionBelow(mGameObject->mBoxColliderComponent) == true   )
			{
				acceleration *= -1;
				mVelocity.y = -.8f;//dir;
			}
		}
		//std::cout << dir << std::endl;
		move(mVelocity);
	}
}

void ItemLogic::move(sf::Vector2f dir)
{
	mGameObject->move(dir);
	mGameObject->mBoxColliderComponent->update();
};
void ItemLogic::move(float x, float y)
{
	mGameObject->move(x,y);		
	mGameObject->mBoxColliderComponent->update();
};