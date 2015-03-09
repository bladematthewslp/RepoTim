#pragma once

#include <SFML/Graphics.hpp>
#include "CState.h"
#include "Player.h"

class FallingState : public CState
{
public:
					FallingState(GameObject* player);
	void			entry(GameObject* player);
	CState*	handleInput(GameObject* player, const sf::Event& event);
	CState*	update(GameObject* player, sf::Time dt, Grid& grid);

private:
	sf::Vector2f	gravity;
	int				spriteCounter;
	int				spriteX;
};