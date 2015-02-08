#include "RyobeBoxCollider.h"
#include "CStateRyobeBlocking.h"
RyobeBoxCollider::RyobeBoxCollider(GameObject* character)
	: BoxColliderComponent(character)
{



}

void RyobeBoxCollider::onCollisionEnter(Grid& grid, BoxColliderComponent* other)
{
	if(other->mGameObject->mName == "PlayerAttackBox")
	{
		CState* newState = std::unique_ptr<CState>(new CStateRyobeBlocking(mGameObject)).release();
		mGameObject->mState = newState;
	}


}