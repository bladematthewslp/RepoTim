#pragma once

#include "CState.h"

class KnockoutState : public CState
{
	
	sf::Vector2f	mVelocity;

public:
	KnockoutState(GameObject* gameObject);

	void		entry(GameObject* player);
	CState*		handleInput(GameObject* player, const sf::Event& event);
	CState*		update(GameObject* player, sf::Time dt, Grid& grid);
};