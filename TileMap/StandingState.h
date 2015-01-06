#pragma once

#include "PlayerState.h"
#include <SFML/Graphics.hpp>

class PlayerLogic;
class GameObject;
class StandingState : public PlayerState
{
public:
					StandingState(GameObject* player);
	void			entry(GameObject* player);

	PlayerState*  handleInput(GameObject* player, Grid& grid, const sf::Event& event);
	
	PlayerState*	update(GameObject* player, sf::Time dt, Grid& grid);

};