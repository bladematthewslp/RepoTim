#include "ProjectileScriptComponent.h"
#include "Clock.h"
#include "ClockScriptComponent.h"
#include "ClockColliderComponent.h"
#include "GameObject.h"

float numCols = 0;

std::array<Vector2D, 4> ClockColliderComponent::screenBounds;

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

	screenBounds[0] = Vector2D(0, 0);
	screenBounds[1] = Vector2D(0, mApplication->getScreenHeight());
	screenBounds[2] = Vector2D(mApplication->getScreenWidth(), mApplication->getScreenHeight());
	screenBounds[3] = Vector2D(mApplication->getScreenWidth(), 0);

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
	
	if (otherCollider != nullptr)
	{

		if (otherCollider->mGameObject.getName() == "Projectile")
		{
			GameObject::Destroy(mGameObject);
			GameObject::Destroy(otherCollider->mGameObject);
			

			Vector2D curPosition = mGameObject.getPosition();
			Vector2D curScale = mGameObject.getScale();
			Vector2D offset = Vector2D((mCollider.xMax - mCollider.xMin) / 2, (mCollider.yMax - mCollider.yMin) / 2);
			if (curScale.x / 2 > .10)
			{
				GameObject* clock1 = GameObject::Create<Clock>();
				clock1->scale(curScale.x * .5, curScale.y * .5);
				clock1->setPosition(curPosition.x - offset.x / 2, curPosition.y + offset.y/2);

				GameObject* clock2 = GameObject::Create<Clock>();
				clock2->scale(curScale.x * .5, curScale.y * .5);
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

				if (mCollider.xMin > otherCollider->mCollider.xMax || otherCollider->mCollider.xMax > mCollider.xMin)
				{
					//OutputDebugString("x\n");

					vel.x *= -1;
					script->setVelocity(vel);
					//mGameObject.move(vel.x, 0);

					otherVel.x *= -1;
					otherScript->setVelocity(otherVel);
					//otherScript->mGameObject.move(otherVel.x, 0);
				}
				if (mCollider.yMin > otherCollider->mCollider.yMax || otherCollider->mCollider.yMax > mCollider.yMin)
				{
					//OutputDebugString("y\n");

					vel.y *= -1;
					script->setVelocity(vel);
					//mGameObject.move(0, vel.y);


					otherVel.y *= -1;
					otherScript->setVelocity(otherVel);
					//otherScript->mGameObject.move(0, otherVel.y);
				}
			}
			

		}
		
		
		
	}

	return otherCollider;
}