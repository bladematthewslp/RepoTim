#pragma once

#include <SFML/Graphics.hpp>
#include "CState.h"

class CStateNinjaDead : public CState
{

public:
	CStateNinjaDead(GameObject* character);

	CState*	update(GameObject* character, sf::Time dt, Grid& grid);
};