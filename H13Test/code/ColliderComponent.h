#pragma once


#include "Component.h"
#include "Vector.h"

struct AABB
{
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	AABB(float minX = 0, float maxX = 0, float minY = 0, float maxY = 0)
		: xMin(minX)
		, xMax(maxX)
		, yMin(minY)
		, yMax(maxY)
	{

	}
};

class ColliderComponent : public Component
{
protected:
	AABB mCollider;
	Vector2D mPosition;
public:
	ColliderComponent(GameObject& gameObject);
	virtual void update();
	Vector2D mPreviousPosition;

	Vector2D getPosition();
	virtual ColliderComponent* checkForCollision();
	const AABB& getCollider() const;
};