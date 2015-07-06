#include "ProjectileScriptComponent.h"
#include "ColliderComponent.h"
#include "ClockScriptComponent.h"
#include "C_Application.h"
#include "QuadTree.h"

ColliderComponent::ColliderComponent(GameObject& gameObject)
	: Component(gameObject)
	, mPosition()
	, mCollider()
	, mPreviousPosition()
	, mParentQuadNode(nullptr)
	, mPrevQuadCollider(nullptr)
	, mNextQuadCollider(nullptr)
{
	mApplication->addComponent<ColliderComponent>(this);

	
	
}

ColliderComponent::~ColliderComponent()
{

}

void ColliderComponent::update()
{
	
	mPreviousPosition = mPosition; 
	mPosition = mGameObject.getPosition();
	if (mGameObject.mRenderComponent)
	{
		auto verts = mGameObject.mRenderComponent->getVertices();
		mCollider.xMin = mPosition.x - std::abs(verts[0].x);
		mCollider.xMax = mPosition.x + std::abs(verts[3].x);
		mCollider.yMin = mPosition.y - std::abs(verts[0].y);
		mCollider.yMax = mPosition.y + std::abs(verts[2].y);
	}
}

void ColliderComponent::setSize(float x, float y, float width, float height)
{
	mCollider.xMin = x;
	mCollider.xMax = x + width;
	mCollider.yMin = y;
	mCollider.yMax = y + height;
}

Vector2D ColliderComponent::getPosition()
{
	return mPosition;
}
ColliderComponent* ColliderComponent::checkForCollision(ColliderComponent* other)
{

	if (other != this)
	{
		Vector2D otherColliderPosition = other->getPosition();
		if ( other->mGameObject.mRenderComponent != nullptr)
		{
			auto verts = other->mGameObject.mRenderComponent->getVertices();
			AABB otherAABB = other->mCollider;

			if (mCollider.xMin > otherAABB.xMax || otherAABB.xMin > mCollider.xMax)
			{
				return nullptr;
			}
			if (mCollider.yMin > otherAABB.yMax || otherAABB.yMin > mCollider.yMax)
			{
				return nullptr;
			}
			return other;
		}
	}

	return nullptr;
	
}

AABB ColliderComponent::getCollider() const
{
	return mCollider;
}