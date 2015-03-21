#pragma once


#include "LogicComponent.h"

class DaggerLogic : public LogicComponent
{
	int speed;
	int mDirection;
public:
	DaggerLogic(GameObject* gameObject);
	void	update(Grid& grid);
	int		getDirection();

};