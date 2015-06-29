#include "ColliderComponent.h"
#include "C_Application.h"
ColliderComponent::ColliderComponent(GameObject& gameObject)
	: Component(gameObject)
	, mPosition()
	, mCollider()
	, mPreviousPosition()
{
	mApplication->addComponent<ColliderComponent>(this);
	
}

void ColliderComponent::update()
{
	mPreviousPosition = mPosition;
	mPosition = mGameObject.getPosition();
	auto verts = mGameObject.mRenderComponent->getVertices();
	mCollider.xMin = mPosition.x - std::abs(verts[0].x);
	mCollider.xMax = mPosition.x + std::abs(verts[3].x);
	mCollider.yMin = mPosition.y - std::abs(verts[0].y);
	mCollider.yMax = mPosition.y + std::abs(verts[2].y);
}

Vector2D ColliderComponent::getPosition()
{
	return mPosition;
}
ColliderComponent* ColliderComponent::checkForCollision()
{

	//for (auto collider = mApplication->mColliderComponents.begin(); collider != mApplication->mColliderComponents.end(); ++collider)
	{
		for (auto collider = mApplication->mColliderComponents.begin(); collider != mApplication->mColliderComponents.end(); ++collider)
		{
			if ((this) == (*collider))
				continue;

			Vector2D otherColliderPosition = (*collider)->getPosition();
			auto verts = (*collider)->mGameObject.mRenderComponent->getVertices();
			AABB otherAABB = (*collider)->mCollider;

			if (mCollider.xMin > otherAABB.xMax || otherAABB.xMin > mCollider.xMax)
			{
				continue;
				//return false;
			}
			if (mCollider.yMin > otherAABB.yMax || otherAABB.yMin > mCollider.yMax)
			{
				continue;
				//return false;
			}


			return (*collider);

			//(*collider)->checkForCollision((*otherCollider));

		}
	}

	return nullptr;
	

	
}

const AABB& ColliderComponent::getCollider() const
{
	return mCollider;
}