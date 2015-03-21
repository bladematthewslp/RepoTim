#pragma once

#include "CState.h"

class CStateNinjaHitAirToGround : public CState
{
	GameObject* player;
	float timerToStand;
public:

	CStateNinjaHitAirToGround(GameObject* character);
	CState*	update(GameObject* character, sf::Time dt, Grid& grid);

};