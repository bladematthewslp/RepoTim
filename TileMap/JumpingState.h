#pragma once

#include <SFML/Graphics.hpp>
#include "CState.h"

class Player;

class JumpingState : public CState
{
public:
	JumpingState(GameObject* player);

	void			entry(GameObject* player);
	
	CState*	handleInput(GameObject* player, const sf::Event& event);
	CState*	update(GameObject* player, sf::Time dt, Grid& grid);
	void			accelerate();
	sf::Vector2f	oldPosition;
	sf::IntRect jumpingSpriteBounds[7];
private:
	sf::Vector2f	gravity;
	int				spriteX;
	int				spriteCounter;
	
};