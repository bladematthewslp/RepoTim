#pragma once

#include "CState.h"

class CStateNinjaDeadAir : public CState
{
	bool		done;
	float		maxFallingSpeed;
public:

	CStateNinjaDeadAir(GameObject* character);
	void		entry(GameObject* character, AttackType attackType);
	CState*		handleInput(GameObject* character, const sf::Event& event);
	CState*		update(GameObject* character, sf::Time dt, Grid& grid);


};