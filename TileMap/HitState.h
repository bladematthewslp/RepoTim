#pragma once

#include <SFML/Graphics.hpp>
#include "CState.h"



class HitState : public CState
{
	float hitVelocity;
public:
	HitState(GameObject* player);
	//CState* handleInput(GameObject* player, const sf::Event& event);
	CState* update(GameObject* player, sf::Time dt, Grid& grid);

};