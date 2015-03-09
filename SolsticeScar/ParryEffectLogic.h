#pragma once

#include "LogicComponent.h"

class ParryEffectLogic : public LogicComponent
{


public:
	ParryEffectLogic(GameObject* gameObject);
	void update(Grid& grid);

	GameObject* ryobeGameObject;

};