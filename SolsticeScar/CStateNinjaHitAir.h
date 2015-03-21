#pragma once

#include <SFML/Graphics.hpp>
#include "CState.h"


class CStateNinjaHitAir : public CState
{
	bool		isAirborne;
	int			damageTimer;
	float		mLaunchSpeed;
	float		mAirSpeed;
public:
	CStateNinjaHitAir(GameObject* character);
	void		entry(GameObject* character, AttackType attackType);
	CState*		handleInput(GameObject* character, const sf::Event& event);
	CState*		update(GameObject* character, sf::Time dt, Grid& grid);
	void		successiveHit(GameObject* character, AttackType attackType);


	float		mHitStartingVelocityX;

};