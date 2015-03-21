#pragma once

#include "CState.h"

class CStateRyobeBlocking : public CState
{

public:
	CStateRyobeBlocking(GameObject* character);
	CState* update(GameObject* character,  sf::Time dt, Grid& grid);



};