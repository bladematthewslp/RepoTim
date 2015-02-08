#pragma once

#include "CState.h"


class DazedState : public CState
{
	float dazedTimer;
public:
	DazedState(GameObject* character);
	CState* update(GameObject* character, sf::Time dt, Grid& grid);

};