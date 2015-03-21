#pragma once


#include <SFML/Graphics.hpp>
#include "CState.h"
#include <string>

class CStateNinjaStanding : public CState
{
	int delayTimer;
public:

	CStateNinjaStanding(GameObject* player);
	virtual void		entry(GameObject* player);
	virtual CState*		handleInput(GameObject* player, const sf::Event& event);
	virtual CState*		update(GameObject* player, sf::Time dt, Grid& grid);


};