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
		sf::FloatRect& otherBox = other->mGameObject->mBoxColliderComponent->getCollisionBox()->getGlobalBounds();
		sf::FloatRect& ryobeBox = mGameObject->mBoxColliderComponent->getCollisionBox()->getGlobalBounds();
		if(other->mGameObject->getPosition().x < mGameObject->getPosition().x)
		{
			float dist = (otherBox.left + otherBox.width) - ryobeBox.left ;
			logic->move(dist, 0);
		}
		else
		{
			float dist = (ryobeBox.left + ryobeBox.width) - otherBox.left ;
			logic->move(-dist, 0);
		}
	}

}