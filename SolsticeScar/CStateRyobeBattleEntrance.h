#pragma once

#include "CState.h"

class CStateRyobeBattleEntrance : public CState
{
	float timerToBeginBattle;
	GameObject*					ryobeHUD;
	GameObject*					mHealthBar;

	int							mMaxBarWidth;
	int							mMaxRectWidth;
	int							mHealthBarWidth;
	int							mHealthBarHeight;
public:
	CStateRyobeBattleEntrance(GameObject* character);
	CState* update(GameObject* character, sf::Time dt, Grid& grid);
};