#pragma once

#include "CState.h"

class CStateNinjaFalling : public CState
{
	std::string previousStateName;
	public:
		CStateNinjaFalling(GameObject* character);

		virtual void		entry(GameObject* player);
		virtual CState*		handleInput(GameObject* player, const sf::Event& event);
		virtual CState*		update(GameObject* player, sf::Time dt, Grid& grid);
};