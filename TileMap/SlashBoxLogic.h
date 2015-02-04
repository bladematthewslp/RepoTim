#pragma once

#include <SFML/Graphics.hpp>
#include "LogicComponent.h"
#include "AttackType.h"
#include <map>
#include <array>




struct Grid;
class SlashBoxLogic : public LogicComponent
{
public:

	

					SlashBoxLogic(GameObject* gameObject);
	void			update(Grid& grid);
	void			init(int dir, Attacks::Name attack, int timeToLast );
	void			setAttackType(Attacks::Name type);
	Attacks::Name	getAttack();
	
	int direction;
	
private:
	
	GameObject*					player;
	int							timer;
	int							maxTime;
	std::map<Attacks::Name, std::array<sf::Vector2f,2>> mSpawnPos;
	Attacks::Name				mAttackType;

	
	
};