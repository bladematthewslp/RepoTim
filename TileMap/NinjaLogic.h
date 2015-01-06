#pragma once

#include <SFML/Graphics.hpp>

#include "LogicComponent.h"

class NinjaLogic : public LogicComponent
{
	GameObject* player;
public:
	NinjaLogic(GameObject* mGameObject);
	void update();
};