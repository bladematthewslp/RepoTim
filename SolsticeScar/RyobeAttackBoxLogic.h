#pragma once

#include "LogicComponent.h"
#include "Helper.h"

class RyobeAttackBoxLogic : public LogicComponent
{
	int timer;
	float timeToExpire;
public:
	RyobeAttackBoxLogic(GameObject* gameObject);
	
	void update(Grid& grid);
	void setTimeToExpire(float time);

};