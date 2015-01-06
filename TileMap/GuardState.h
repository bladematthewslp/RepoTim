#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "PlayerState.h"

class GuardState : public PlayerState
{
	int spriteX;
public:
						GuardState(GameObject* player);
	void				entry(GameObject* player);
	PlayerState*		handleInput(GameObject* player, Grid& grid, const sf::Event& event);
	PlayerState*		update(GameObject* player, sf::Time dt, Grid& grid);
};


