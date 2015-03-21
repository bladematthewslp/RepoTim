#pragma once

#include "CState.h"


class DeadAirState : public CState
{
	sf::Vector2f	hitVelocity;
	bool			dead;
public:
	DeadAirState(GameObject* player);
	//CState* handleInput(GameObject* player, const sf::Event& event);
	CState* update(GameObject* player, sf::Time dt, Grid& grid);
};