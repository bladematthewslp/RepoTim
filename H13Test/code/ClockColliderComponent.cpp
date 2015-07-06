#include "Clock.h"
#include "ClockScriptComponent.h"
#include "ClockColliderComponent.h"
#include "GameObject.h"

ClockColliderComponent::ClockColliderComponent(GameObject& gameObject)
	: ColliderComponent(gameObject)
{
	if (mGameObject.mRenderComponent)
	{
		Vector2D pos = mGameObject.getPosition();
		auto verts = mGameObject.mRenderComponent->getVertices();
		mCollider.xMin = pos.x - std::abs(verts[0].x);
		mCollider.xMax = pos.x + std::abs(verts[3].x);
		mCollider.yMin = pos.y - std::abs(verts[0].y);
		mCollider.yMax = pos.y + std::abs(verts[2].y);
	}

}


ClockColliderComponent::~ClockColliderComponent()
{
}

void ClockColliderComponent::update()
{
	ColliderComponent::update();
}

ColliderComponent* ClockColliderComponent::checkForCollision(ColliderComponent* other)
{
 	ClockScriptComponent* script = dynamic_cast<ClockScriptComponent*>(mGameObject.mScriptComponent);
	


	ColliderComponent* otherCollider = ColliderComponent::checkForCollision(other);
	
	if (otherCollider != nullptr && mEnabled == true)
	{

		if (otherCollider->mGameObject.getName() == "Projectile")
		{
			
			GameObject::Destroy(mGameObject);
			GameObject::Destroy(otherCollider->mGameObject);
			mEnabled = false;

			Vector2D curPosition = mGameObject.getPosition();
			Vector2D curScale = mGameObject.getScale();
			Vector2D offset = Vector2D((mCollider.xMax - mCollider.xMin) / 2, (mCollider.yMax - mCollider.yMin) / 2);
			if (curScale.x / 2 < .10)
			{
				GameObject* clock1 = GameObject::Create<Clock>();
				clock1->scale(curScale.x * .5f, curScale.y * .5f);
				clock1->setPosition(curPosition.x - offset.x / 2, curPosition.y + offset.y/2);

				GameObject* clock2 = GameObject::Create<Clock>();
				clock2->scale(curScale.x * .5f, curScale.y * .5f);
				clock2->setPosition(curPosition.x + offset.x / 2, curPosition.y - offset.y/2);

			}
		}
		
		if (otherCollider->mGameObject.getName() == "Clock")
		{
			
			ClockScriptComponent* otherScript = dynamic_cast<ClockScriptComponent*>(otherCollider->mGameObject.mScriptComponent);
			if (script != nullptr && otherScript != nullptr)
			{
				Vector2D vel = script->getVelocity();
				Vector2D otherVel = dynamic_cast<ClockScriptComponent*>(otherCollider->mGameObject.mScriptComponent)->getVelocity();
				Vector2D pos = mGameObject.getPosition();
				Vector2D otherPos = otherCollider->mGameObject.getPosition();

				AABB otherAABB = otherCollider->getCollider();
				
				if (mCollider.xMin > otherAABB.xMax || otherAABB.xMax > mCollider.xMin)
				{

					vel.x *= -1;
					script->setVelocity(vel);

					otherVel.x *= -1;
					otherScript->setVelocity(otherVel);
				}
				if (mCollider.yMin > otherAABB.yMax || otherAABB.yMax > mCollider.yMin)
				{
					vel.y *= -1;
					script->setVelocity(vel);


					otherVel.y *= -1;
					otherScript->setVelocity(otherVel);
				}

				
			}
			

		}
		
		
		
	}

	return otherCollider;
}