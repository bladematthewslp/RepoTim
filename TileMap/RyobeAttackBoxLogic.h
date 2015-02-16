#pragma once

#include "LogicComponent.h"
#include "Helper.h"

class RyobeAttackBoxLogic : public LogicComponent
{
	int timer;
public:
	RyobeAttackBoxLogic(GameObject* gameObject);
	
	void update(Grid& grid);


};