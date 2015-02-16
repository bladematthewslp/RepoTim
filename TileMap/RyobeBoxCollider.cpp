#include "RyobeBoxCollider.h"
#include "RyobeLogic.h"
//#include "CStateRyobeBlocking.h"
RyobeBoxCollider::RyobeBoxCollider(GameObject* character)
	: BoxColliderComponent(character)
{
	//this->setVisible(true);


}

void RyobeBoxCollider::onCollisionEnter(Grid& grid, BoxColliderComponent* other)
{
	

} 

void RyobeBoxCollider::onCollisionStay(Grid& grid, BoxColliderComponent* other)
{
	RyobeLogic* logic = dynamic_cast<RyobeLogic*>(mGameObject->mLogicComponent);

	if(other->mGameObject->mName == "Lightning")
	{
		if(other->mGameObject->getPosition().x < mGameObject->getPosition().x)
		{
			logic->move(logic->getVelocity().x, 0);
			std::cout << "LIGHTNING LEFT" << std::endl;
		}
		else
		{
			logic->move(-logic->getVelocity().x, 0);
			std::cout << "LIGHTNING RIGHT" << std::endl;
		}
	}

}