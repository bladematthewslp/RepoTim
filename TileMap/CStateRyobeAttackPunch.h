#pragma once

#include "CState.h"


class CStateRyobeAttackPunch : public CState
{

public:
	CStateRyobeAttackPunch(GameObject* character);

	CState*	update(GameObject* character, sf::Time dt, Grid& grid);
};