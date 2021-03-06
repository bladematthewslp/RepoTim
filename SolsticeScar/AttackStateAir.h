#pragma once

#include <SFML/Graphics.hpp>
#include "CState.h"
#include "StandingState.h"
#include <queue>
class GameObject;
class AttackStateAir : public CState
{
	GameObject* slashBox;
	bool soundEffectPlayed;
	int	spriteX;
	int slashNumber;
	int timer;
	CState* previousState;
	float airJumpSpeed;
	bool attackBoxCreated;

public:
	AttackStateAir(GameObject* player);

	void entry(GameObject* player);
	void exit(GameObject* player);

	CState*	handleInput(GameObject* player,const sf::Event& event);
	CState*	update(GameObject* player, sf::Time dt, Grid& grid);

	void				playSound(SoundEffect::ID, PlayerLogic*);
	


};