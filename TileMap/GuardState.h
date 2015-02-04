#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "CState.h"

class GuardState : public CState
{
	int spriteX;
	int timer;
public:
						GuardState(GameObject* player);
	void				entry(GameObject* player);
	CState*		handleInput(GameObject* player, const sf::Event& event);
	CState*		update(GameObject* player, sf::Time dt, Grid& grid);
	void		block(GameObject* player);
};


