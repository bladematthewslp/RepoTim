#pragma once


#include "CState.h"

class CStateRyobeAttacking : public CState
{
		
	public:
		
		std::string attackType;
		bool daggerThrown;

		CStateRyobeAttacking(GameObject* character);
		CState*	update(GameObject* character, sf::Time dt, Grid& grid);
		void entry(GameObject* character);

		bool isTeleporting(); 
	private:
		int			timer;
		float		embracerSpeed;
		bool		teleporting;
		float		teleportTimer;

		int			chargeLoopCounter;

		bool		embracerAttackBoxCreated;

};