#pragma once

#include <SFML/Graphics.hpp>
#include "PlayerState.h"

class Player;

class JumpingState : public PlayerState
{
public:
	JumpingState(GameObject* player);

	void			entry(GameObject* player);
	
	PlayerState*	handleInput(GameObject* player, Grid& grid, const sf::Event& event);
	PlayerState*	update(GameObject* player, sf::Time dt, Grid& grid);
	void			accelerate();
	sf::Vector2f	oldPosition;
	sf::IntRect jumpingSpriteBounds[7];
private:
	sf::Vector2f	gravity;
	int				spriteX;
	int				spriteCounter;
	
};