#pragma once

#include <SFML/Graphics.hpp>
#include "CState.h"



class HitAirState : public CState
{
	sf::Vector2f hitVelocity;
public:
	HitAirState(GameObject* player);
	//CState* handleInput(GameObject* player, const sf::Event& event);
	CState* update(GameObject* player, sf::Time dt, Grid& grid);

};