#include "QuadTree.h"
Node::Node()
{
}


Node* Node::BuildQuadTree(Vector2D center, float halfWidth, int stopDepth)
{
	if (stopDepth < 0)
		return nullptr;
	else
	{
		// Construct and fill in ’root’ of this subtree
		Node* pNode = new Node();
		pNode->center = center;
		pNode->halfWidth = halfWidth;
		//pNode->halfHeight = halfHeight;
		pNode->mColliderList = nullptr;


		// Recursively construct the eight children of the subtree
		Vector2D offset;
		float step = halfWidth * 0.5f;
		//float stepY = halfHeight * 0.5f;
		for (int i = 0; i < 4; i++)
		{
			offset.x = ((i & 1) ? step : -step);
			offset.y = ((i & 2) ? step : -step);
			pNode->pChild[i] = BuildQuadTree(center + offset, step, stopDepth - 1);

		}
		return pNode;
	}
}

void Node::InsertObject(Node* pTree, ColliderComponent* pObject)
{
	int index = 0, straddle = 0;
	for (int i = 0; i < 2; i++)
	{
		float delta = pObject->mPosition.x - pTree->center.x;
		float distanceFromXMin = std::abs(pTree->center.x - pObject->mCollider.xMin);
		float distanceFromXMax = std::abs(pTree->center.y - pObject->mCollider.xMax);
		float distanceFromYMin = std::abs(pTree->center.y - pObject->mCollider.yMin);
		float distanceFromYMax = std::abs(pTree->center.y - pObject->mCollider.yMax);
		if (	std::abs(delta) < distanceFromXMin
			&&	std::abs(delta) < distanceFromXMax
			&&	std::abs(delta) < distanceFromYMin
			&&	std::abs(delta) < distanceFromYMax)
		{
			straddle = 1;
			break;
		}
		if (delta > 0.0f)
			index |= (1 << i);
	}

	if (!straddle && pTree->pChild[index])
	{
		InsertObject(pTree->pChild[index], pObject);
	}
	else
	{
		// Straddling, or no child node to descend into, so link
		// object into linked list
		
		pObject->mNextQuadCollider = pTree->mColliderList;
		if(pTree->mColliderList)
			pTree->mColliderList->mPrevQuadCollider = pObject;
		pTree->mColliderList = pObject;
		pObject->mParentQuadNode = pTree;
	}
}

void Node::RemoveObject(ColliderComponent* collider)
{
	if (collider->mPrevQuadCollider == nullptr)
	{
		collider->mParentQuadNode->mColliderList = collider->mNextQuadCollider;
	}
	else
		collider->mPrevQuadCollider->mNextQuadCollider = collider->mNextQuadCollider;

	if (collider->mNextQuadCollider != nullptr)
		collider->mNextQuadCollider->mPrevQuadCollider = collider->mPrevQuadCollider;
}

void Node::TestAllCollisions(Node* pTree)
{
	// Keep track of all ancestor object lists in a stack
	const int MAX_DEPTH = 40;
	static Node *ancestorStack[MAX_DEPTH];
	static int depth = 0; // ’Depth == 0’ is invariant over calls
	// Check collision between all objects on this level and all
	// ancestor objects. The current level is included as its own
	// ancestor so all necessary pairwise tests are done
	ancestorStack[depth++] = pTree;
	for (int n = 0; n < depth; n++)
	{
		ColliderComponent *pA, *pB;
		for (pA = ancestorStack[n]->mColliderList; pA; pA = pA->mNextQuadCollider)
		{
			for (pB = pTree->mColliderList; pB != nullptr; pB = pB->mNextQuadCollider)
			{
				// Avoid testing both A->B and B->A
				if (pA == pB)
					break;
				// Now perform the collision test between pA and pB in some manner
				pA->checkForCollision(pB);


			}
		}
	}
	// Recursively visit all existing children
	for (int i = 0; i < 4; i++)
	{
		if (pTree->pChild[i])
			TestAllCollisions(pTree->pChild[i]);
	}
	// Remove current node from ancestor stack before returning
	depth--;
}