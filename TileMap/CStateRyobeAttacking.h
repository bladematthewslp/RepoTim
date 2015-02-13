#pragma once


#include "CState.h"

class CStateRyobeAttacking : public CState
{
	public:
		enum RyobeAttack
		{
			Dagger,
			SwordAttack
		};
		int attackType;
		bool daggerThrown;

		CStateRyobeAttacking(GameObject* character);
		CState*	update(GameObject* character, sf::Time dt, Grid& grid);
		void entry(GameObject* character);

		

};