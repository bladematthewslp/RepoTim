#pragma once

#include <SFML/Graphics.hpp>
#include "LogicComponent.h"

class SlashBoxLogic : public LogicComponent
{
	GameObject* player;
public:
	SlashBoxLogic(GameObject* gameObject);
	void update();
	int direction;
	void init();
};