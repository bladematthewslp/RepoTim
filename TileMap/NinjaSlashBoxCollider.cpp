#include "NinjaSlashBoxCollider.h"
#include "NinjaSlashBoxLogic.h"
#include "PlayerLogic.h"

#include <iostream>

NinjaSlashBoxCollider::NinjaSlashBoxCollider(GameObject* gameObject)
	: BoxColliderComponent(gameObject)
{


}


void NinjaSlashBoxCollider::onCollisionEnter(Grid& grid, BoxColliderComponent* other)
{
	//std::cout << other->mGameObject->mName << std::endl;
	NinjaSlashBoxLogic* logic = dynamic_cast<NinjaSlashBoxLogic*>(mGameObject->mLogicComponent);

	if(other->mGameObject->mName == "Player")
	{
		dynamic_cast<PlayerLogic*>(other->mGameObject->mLogicComponent)->hit(logic->mSpawningCharacter, logic->getAttackName());
		
		System::removeGameObject(mGameObject);
	}
	
}