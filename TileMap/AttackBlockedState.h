#pragma once

#include "CState.h"

class AttackBlockedState : public CState
{

public:
	AttackBlockedState(GameObject* character);

	CState* update(GameObject* character, sf::Time dt, Grid& grid);


};