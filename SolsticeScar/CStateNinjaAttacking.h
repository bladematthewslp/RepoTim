#pragma once

#include <SFML/Graphics.hpp>
#include "CState.h"


class CStateNinjaAttacking : public CState
{
	bool	slashBoxCreated;
	int		timer;
public:

	CStateNinjaAttacking(GameObject* player);
	virtual void		entry(GameObject* player);
	virtual CState*		handleInput(GameObject* player, Grid& grid, const sf::Event& event);
	virtual CState*		update(GameObject* player, sf::Time dt, Grid& grid);
};