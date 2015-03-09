#pragma once

#include "CState.h"
#include <SFML/Graphics.hpp>

class PlayerLogic;
class GameObject;
class StandingState : public CState
{
public:
					StandingState(GameObject* player);
	void			entry(GameObject* player);

	CState*  handleInput(GameObject* player, const sf::Event& event);
	
	CState*	update(GameObject* player, sf::Time dt, Grid& grid);

};