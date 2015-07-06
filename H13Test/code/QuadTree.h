#pragma once

#include "ColliderComponent.h"


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
