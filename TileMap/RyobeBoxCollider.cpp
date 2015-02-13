#include "RyobeBoxCollider.h"
#include "RyobeLogic.h"
//#include "CStateRyobeBlocking.h"
RyobeBoxCollider::RyobeBoxCollider(GameObject* character)
	: BoxColliderComponent(character)
{



}

void RyobeBoxCollider::onCollisionEnter(Grid& grid, BoxColliderComponent* other)
{

	
	if(other->mGameObject->mName == "PlayerAttackBox")
	{
		dynamic_cast<RyobeLogic*>(mGameObject->mLogicComponent)->hit();
		//CState* newState = std::unique_ptr<CState>(new CStateRyobeBlocking(mGameObject)).release();
		//mGameObject->mState = newState;
	}
	

}