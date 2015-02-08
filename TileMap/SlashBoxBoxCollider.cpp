#include "SlashBoxBoxCollider.h"
#include "NinjaLogic.h"
#include "SlashBoxLogic.h"
#include "AttackType.h"
#include "System.h"

SlashBoxBoxCollider::SlashBoxBoxCollider(GameObject* gameObject)
	: BoxColliderComponent(gameObject)
{
	//this->setVisible(true);
	this->mCollisionBox.setSize(sf::Vector2f(120,120));
	//std::cout << "NEW BOX " << std::endl;
}

void SlashBoxBoxCollider::onCollisionEnter(Grid& grid, BoxColliderComponent* other)
{
	SlashBoxLogic* logic = dynamic_cast<SlashBoxLogic*>(mGameObject->mLogicComponent);
	if(other->mGameObject->mName == "Ninja")
	{
		dynamic_cast<NinjaLogic*>(other->mGameObject->mLogicComponent)->hit(other->mGameObject, logic->getAttack());
		System::removeGameObject(mGameObject);
	}
	if(other->mGameObject->mLayerName == Layer::Enemy)
	{
		System::removeGameObject(mGameObject);
	}
	
	/*if(other->mGameObject->mName == "Ninja")
	{
		System::removeGameObject(other->mGameObject);
	}*/
}