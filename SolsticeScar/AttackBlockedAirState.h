#pragma once
#include "CState.h"

class AttackBlockedAirState : public CState
{
	sf::Vector2f	hitVelocity;
public:
	AttackBlockedAirState(GameObject* character);
	CState* update(GameObject* character, sf::Time dt, Grid& grid);

};