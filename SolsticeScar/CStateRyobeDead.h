#pragma once

#include "CState.h"


class CStateRyobeDead : public CState
{
	sf::Vector2f mVelocity;
public:
	CStateRyobeDead(GameObject* character);
	CState*			update(GameObject* character, sf::Time dt, Grid& grid);


};