#pragma once


#include "CState.h"

class RyobeLogic;

class CStateRyobeAttacking : public CState
{
		GameObject* parryEffect;
	public:
		
		std::string attackType;
		bool daggerThrown;

		CStateRyobeAttacking(GameObject* character);
		CState*	update(GameObject* character, sf::Time dt, Grid& grid);
		void entry(GameObject* character);

		bool isTeleporting(); 
		void		playSound(SoundEffect::ID, RyobeLogic*);
	private:
		bool		soundEffectPlayed;
		int			timer;
		
		float		fellCrescentSpeed;
		bool		fellCrescentAttackBoxCreated;

		float		embracerSpeed;
		bool		embracerAttackBoxCreated;

		bool		teleporting;
		float		teleportTimer;

		int			chargeLoopCounter;

		

};