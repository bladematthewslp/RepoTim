#pragma once

#include <SFML/Graphics.hpp>
#include "LogicComponent.h"
#include "AttackType.h"
#include <map>
#include <array>

class NinjaSlashBoxLogic : public LogicComponent
{
public:
	NinjaSlashBoxLogic(GameObject* gameObject);
	void init(GameObject& character, int dir, Attacks::Name attack, int timeToLast );
	void update(Grid& grid);
	Attacks::Name	getAttackName();


	GameObject*		mSpawningCharacter;
private:
	
	Attacks::Name	mAttackName;

	int				timer;
	int				maxTime;

	std::map<Attacks::Name, std::array<sf::Vector2f, 2>>	mSpawnPos;

};