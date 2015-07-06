#pragma once


#include "Component.h"
#include "Vector2D.h"



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
	friend struct Node;
protected:
	
	Vector2D					mPosition;
	

	AABB						mCollider;

	// variables for quad-tree
	Node*						mParentQuadNode;
	ColliderComponent*			mPrevQuadCollider;
	ColliderComponent*			mNextQuadCollider;


public:
	ColliderComponent(GameObject& gameObject);
	~ColliderComponent();
	
	virtual void				update();
	
	Vector2D					mPreviousPosition;
	Vector2D					getPosition();
	virtual ColliderComponent*	checkForCollision(ColliderComponent* other);
	AABB						getCollider() const; 

	void						setSize(float xMin, float yMin, float xMax, float yMax);
};