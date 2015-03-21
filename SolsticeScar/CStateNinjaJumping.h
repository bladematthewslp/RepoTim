#pragma once

#include "CState.h"

class CStateNinjaJumping : public CState
{

public:
	CStateNinjaJumping(GameObject* character);
	void entry(GameObject* character);			
	CState* handleInput(GameObject* character, const sf::Event& event);
	CState* update(GameObject* character, sf::Time dt, Grid& grid);

};