#pragma once

#include "LogicComponent.h"



class HealthBarLogic : public LogicComponent
{
public:
	HealthBarLogic(GameObject* gameObject);

	void updateHealth(int num);

};