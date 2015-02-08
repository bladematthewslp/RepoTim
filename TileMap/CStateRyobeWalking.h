#pragma once

#include "CState.h"


class CStateRyobeWalking : public CState
{

public:
	CStateRyobeWalking(GameObject* character);
	CState*		update(GameObject* character, sf::Time dt, Grid& grid);

};