#pragma once
#include "ColliderComponent.h"
#include "GameObject.h"
#include <vector>
#include <array>
#include <memory>
#include <list>


/*
struct Object
{
	Vector2D center;
	AABB aabb;

	Object* pNextObject;
	ColliderComponent* collider;
	Object(ColliderComponent* col)
	{
		collider = col;
		aabb = col->mCollider;
		center.x = (aabb.xMin + aabb.xMax) / 2;
		center.y = (aabb.yMin + aabb.yMax) / 2;
	}
};
*/
struct Node
{
	Vector2D center;
	float halfWidth;
	float halfHeight;
	Node* pChild[4];
	ColliderComponent* mColliderList;

	Node();

	static Node* BuildQuadTree(Vector2D center, float halfWidth, int stopDepth);
	void InsertObject(Node* pTree, ColliderComponent* collider);
	static void RemoveObject(ColliderComponent* collider);

	void TestAllCollisions(Node* pTree);
};
