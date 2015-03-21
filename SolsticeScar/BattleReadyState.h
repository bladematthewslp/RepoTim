#pragma once

#include "CState.h"

class BattleReadyState : public CState
{
	float timer;
	float maxTime;
public:
	BattleReadyState(GameObject* character);
	CState* update(GameObject* character, sf::Time dt, Grid& grid);
	void	setMaxTime(float num);
};


