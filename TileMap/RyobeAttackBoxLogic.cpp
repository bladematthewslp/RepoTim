#include "RyobeAttackBoxLogic.h"

RyobeAttackBoxLogic::RyobeAttackBoxLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
	, timer(0)
{
	

}

void RyobeAttackBoxLogic::update(Grid& grid)
{

	timer++;
	if(timer > 25)
	{
		System::removeGameObject(mGameObject);
	}
}