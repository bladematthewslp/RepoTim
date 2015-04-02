#pragma once

#include "CState.h"


class CStateNinjaHitDraggedState : public CState
{

public:
	CStateNinjaHitDraggedState(GameObject* character);
	void		entry(GameObject* character);
	CState*		handleInput(GameObject* character, const sf::Event& event);
	CState*		update(GameObject* character, sf::Time dt, Grid& grid);

};