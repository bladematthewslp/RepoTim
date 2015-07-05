#pragma once


#include "Component.h"
#include "Vector.h"

struct Node;

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
public:
	AABB mCollider;
	Vector2D mPosition;
	Node* mParentQuadNode;
	ColliderComponent* mPrevQuadCollider;
	ColliderComponent* mNextQuadCollider;

	ColliderComponent(GameObject& gameObject);
	~ColliderComponent();
	virtual void update();
	Vector2D mPreviousPosition;

	Vector2D getPosition();
	virtual ColliderComponent* checkForCollision(ColliderComponent* other);
	const AABB& getCollider() const; 

	void setSize(float xMin, float yMin, float xMax, float yMax);
};