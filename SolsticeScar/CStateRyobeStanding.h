#pragma once

#include "CState.h"

class CStateRyobeStanding : public CState
{
	float		timer;
	bool		startTimer;
public:
	CStateRyobeStanding(GameObject* character);
	CState*		update(GameObject* character, sf::Time dt, Grid& grid);

};