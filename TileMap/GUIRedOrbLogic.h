#pragma once

#include "LogicComponent.h"
class GUIRedOrbLogic : public LogicComponent
{
	sf::Time	deltaTime;
	float		timerGUI;
public:
	GUIRedOrbLogic(GameObject* gameObject);
	void	update(Grid& grid);
	void	showRedOrbGUI();

};