#pragma once

#include <SFML/Graphics.hpp>
#include "PlayerState.h"
#include "PlayerAttacks.h"
#include <queue>
class GameObject;
class AttackState : public PlayerState
{
	int	spriteX;
	int slashNumber;
public:
	AttackState(GameObject* player);
	void entry(GameObject* player);
	PlayerState*	handleInput(GameObject* player, Grid& grid, const sf::Event& event);
	PlayerState*	update(GameObject* player, sf::Time dt, Grid& grid);

	PlayerAttack*		currentCommand;
	std::queue<PlayerAttack*>		attackQueue;

};