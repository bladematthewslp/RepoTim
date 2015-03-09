#pragma once

#include "LogicComponent.h"



class HealthBarLogic : public LogicComponent
{

	int maxBarWidth;
	int maxRectWidth;
	
	int healthBarHeight;
	
public:
	HealthBarLogic(GameObject* gameObject);

	void updateHealth(int num);

};