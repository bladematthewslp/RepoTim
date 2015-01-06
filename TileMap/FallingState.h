#pragma once

#include <SFML/Graphics.hpp>
#include "PlayerState.h"
#include "Player.h"

class FallingState : public PlayerState
{
public:
					FallingState(GameObject* player);
	void			entry(GameObject* player);
	PlayerState*	handleInput(GameObject* player, Grid& grid, const sf::Event& event);
	PlayerState*	update(GameObject* player, sf::Time dt, Grid& grid);

private:
	sf::Vector2f	gravity;
	int				spriteCounter;
	int				spriteX;
};