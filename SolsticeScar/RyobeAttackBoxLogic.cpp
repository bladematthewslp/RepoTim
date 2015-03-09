#include "RyobeAttackBoxLogic.h"

RyobeAttackBoxLogic::RyobeAttackBoxLogic(GameObject* gameObject)
	: LogicComponent(gameObject)
	, timer(0)
	, timeToExpire(0.0f)
{
	

}

void RyobeAttackBoxLogic::update(Grid& grid)
{

	timer++;
	if(timer > timeToExpire)
	{
		System::removeGameObject(mGameObject);
	}
}

void RyobeAttackBoxLogic::setTimeToExpire(float time)
{
	timeToExpire = time;
}