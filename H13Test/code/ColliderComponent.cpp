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
	Node::RemoveObject(this);
}

void ColliderComponent::update()
{
	ClockScriptComponent* script = dynamic_cast<ClockScriptComponent*>(mGameObject.mScriptComponent);
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

	if (mCollider.xMin < 0)
	{
		if (script != nullptr)
		{
			auto vel = script->getVelocity();
			vel.x *= -1;
			script->setVelocity(vel);
			mGameObject.move(-mCollider.xMin, 0);
		}
	}
	if (mCollider.xMax > mApplication->getScreenWidth())
	{
		if (script != nullptr)
		{
			auto vel = script->getVelocity();
			vel.x *= -1;
			script->setVelocity(vel);
			mGameObject.move(-(mCollider.xMax - mApplication->getScreenWidth()), 0);
		}
	}

	if (mCollider.yMin < 0)
	{
		if (script != nullptr)
		{
			auto vel = script->getVelocity();
			vel.y *= -1;
			script->setVelocity(vel);
			mGameObject.move(0, -mCollider.yMin);
		}
	}
	if (mCollider.yMax > mApplication->getScreenHeight())
	{

		if (script != nullptr)
		{
			auto vel = script->getVelocity();
			vel.y *= -1;
			script->setVelocity(vel);
			mGameObject.move(0, -(mCollider.yMax - mApplication->getScreenHeight()));// vel.y);
		}
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

	ClockScriptComponent* script = dynamic_cast<ClockScriptComponent*>(mGameObject.mScriptComponent);

	

	if (other != this)
	{
		Vector2D otherColliderPosition = other->getPosition();
		if ( other->mGameObject.mRenderComponent != nullptr)
		{
			auto verts = other->mGameObject.mRenderComponent->getVertices();
			AABB otherAABB = other->mCollider;

			if (mCollider.xMin > otherAABB.xMax || otherAABB.xMin > mCollider.xMax)
			{
				//continue;
				return nullptr;
			}
			if (mCollider.yMin > otherAABB.yMax || otherAABB.yMin > mCollider.yMax)
			{
				//continue;
				return nullptr;
			}


			return other;
		}
	}

	/*
	//for (auto collider = mApplication->mColliderComponents.begin(); collider != mApplication->mColliderComponents.end(); ++collider)
	{
		for (auto collider = mApplication->mColliderComponents.begin(); collider != mApplication->mColliderComponents.end(); ++collider)
		{
			if ((this) == (*collider))
				continue;

			Vector2D otherColliderPosition = (*collider)->getPosition();
			if ((*collider)->mGameObject.mRenderComponent)
			{
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
			}

		}
	}

	return nullptr;
	*/

	
}

const AABB& ColliderComponent::getCollider() const
{
	return mCollider;
}