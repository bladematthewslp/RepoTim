#pragma once


#include "CState.h"


class WinState : public CState
{

public:
	WinState(GameObject* character);
	CState* update(GameObject* character, sf::Time dt, Grid& grid);


};