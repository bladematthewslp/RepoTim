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

ColliderComponent* ClockColliderComponent::checkForCollision()
{
 	ClockScriptComponent* script = dynamic_cast<ClockScriptComponent*>(mGameObject.mScriptComponent);
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



	ColliderComponent* collidedCol = ColliderComponent::checkForCollision();
	if (collidedCol != nullptr)
	{
		if (collidedCol->mGameObject.getName() == "Projectile")
		{
			GameObject::Destroy(mGameObject);
			GameObject::Destroy(collidedCol->mGameObject);

			Vector2D curPosition = mGameObject.getPosition();
			Vector2D curScale = mGameObject.getScale();
		

			GameObject* clock1 = GameObject::Create<Clock>();
			clock1->scale(curScale.x * .5, curScale.y * .5);
			clock1->setPosition(curPosition.x - 50, curPosition.y + 50);

			GameObject* clock2 = GameObject::Create<Clock>();
			clock2->scale(curScale.x * .5, curScale.y * .5);
			clock2->setPosition(curPosition.x + 50, curPosition.y - 50);

		}
		/*
		if (otherCollider->mGameObject.getName() == "Clock")
		{
			if (script != nullptr)
			{
				auto vel = script->getVelocity();
				auto otherVel = dynamic_cast<ClockScriptComponent*>(otherCollider->mGameObject.mScriptComponent)->getVelocity();
				auto pos = mGameObject.getPosition();
				if (mCollider.xMax > otherCollider->getCollider().xMin)// || otherCollider->getCollider().xMax < mCollider.xMin)
				{
					float space = mCollider.xMax - otherCollider->getCollider().xMin;
					vel.x *= -1;
					script->setVelocity(vel);
					//mGameObject.setPosition(mPreviousPosition);
					mGameObject.move(vel.x, 0);

					otherVel.x *= -1;
					dynamic_cast<ClockScriptComponent*>(otherCollider->mGameObject.mScriptComponent)->setVelocity(otherVel);
					//otherCollider->mGameObject.setPosition(otherCollider->mPreviousPosition);
					otherCollider->mGameObject.move(otherVel.x, 0);
					/*
					Vector2D top = Vector2D(otherCollider->getCollider().xMin, otherCollider->getCollider().yMin);
					Vector2D bottom = Vector2D(otherCollider->getCollider().xMin, otherCollider->getCollider().yMax);
					Vector2D side = bottom - top;
					Vector2D normal = side.rotateCCW().normalized();

					Vector2D relativePos = otherCollider->mGameObject.getPosition() - top;
					float dot = normal.dot(relativePos);
					if (dot < 0)
					{
					vel = vel - normal * 2 * vel.dot(normal);
					}

					script->setVelocity(vel);
					mGameObject.move(vel.x, 0);



					top = Vector2D(mCollider.xMax, mCollider.yMin);
					bottom = Vector2D(mCollider.xMax, mCollider.yMax);
					side = bottom - top;
					normal = side.rotateCCW().normalized();
					pos = mGameObject.getPosition();
					relativePos = pos - top;
					dot = normal.dot(relativePos);

					if (dot < 0)
					{
					otherVel = otherVel - normal * 2 * otherVel.dot(normal);
					}
					//otherVel.x *= -1.0f;
					dynamic_cast<ClockScriptComponent*>(otherCollider->mGameObject.mScriptComponent)->setVelocity(otherVel);
					otherCollider->mGameObject.move(otherVel.x, 0);
					
				}

				//vel = script->getVelocity();
				//otherVel = dynamic_cast<ClockScriptComponent*>(otherCollider->mGameObject.mScriptComponent)->getVelocity();
				//pos = mGameObject.getPosition();

				else if (mCollider.yMax > otherCollider->getCollider().yMin)//|| otherCollider->getCollider().yMax < mCollider.yMin)
				{
					OutputDebugString("y\n");
					vel.y *= -1.0f;
					script->setVelocity(vel);
					//mGameObject.setPosition(mPreviousPosition);
					mGameObject.move(0, vel.y);
					/*

					Vector2D topLeft = Vector2D(otherCollider->getCollider().xMin, otherCollider->getCollider().yMin);
					Vector2D topRight = Vector2D(otherCollider->getCollider().xMax, otherCollider->getCollider().yMin);
					Vector2D top = topRight - topLeft;
					Vector2D normal = top.rotateCW().normalized();

					Vector2D relativePos = otherCollider->mGameObject.getPosition() - topLeft;
					float dot = normal.dot(relativePos);
					if (dot < 0)
					{
					vel = vel - normal * 2 * vel.dot(normal);
					}
					//vel.y *= -1.0f;
					script->setVelocity(vel);
					mGameObject.move(0, vel.y);


					topLeft = Vector2D(mCollider.xMin, mCollider.yMin);
					topRight = Vector2D(mCollider.xMax, mCollider.yMin);
					top = topRight - topLeft;
					normal = top.rotateCW().normalized();

					relativePos = pos - topLeft;
					dot = normal.dot(relativePos);
					if (dot < 0)
					{
					otherVel = otherVel - normal * 2 * otherVel.dot(normal);
					}
					
					otherVel.y *= -1.0f;
					dynamic_cast<ClockScriptComponent*>(otherCollider->mGameObject.mScriptComponent)->setVelocity(otherVel);
					//otherCollider->mGameObject.setPosition(otherCollider->mPreviousPosition);
					otherCollider->mGameObject.move(0, otherVel.y);
				}

			}
		}
		*/
		
	}

	return collidedCol;
}