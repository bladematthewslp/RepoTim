#pragma once


#include "LogicComponent.h"

class BloodAnimationLogic : public LogicComponent
{

public:
	BloodAnimationLogic(GameObject* gameObject);
	void	update(Grid& grid);
};