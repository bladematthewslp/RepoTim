#pragma once

#include "LogicComponent.h"
#include "RyobeRender.h"


class RyobeLogic : public LogicComponent
{

public:
	RyobeLogic(GameObject* gameObject);
	void	update(Grid& grid);
};