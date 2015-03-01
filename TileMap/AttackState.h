#pragma once

#include <SFML/Graphics.hpp>
#include "CState.h"
#include "StandingState.h"
#include <queue>
class GameObject;
class AttackState : public CState
{
	bool soundEffectPlayed;
	int timeInState;
	int	spriteX;
	int slashNumber;
	int timer;
	int delayTimer;
	GameObject&			mGameObject;
public:
	AttackState(GameObject* player);
	void				entry(GameObject* player);
	CState*				handleInput(GameObject* player,const sf::Event& event);
	CState*				update(GameObject* player, sf::Time dt, Grid& grid);
	GameObject*			createSlashBox();
	//std::queue<PlayerAttack*>		attackQueue;

	void				setAttack(Attacks::Name);

};