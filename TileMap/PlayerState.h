#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

//class Player;
struct Grid;
class Component;
class PlayerLogic;

class GameObject;
class CState
{
		std::string mStateName;
	public:
		CState(std::string name = "CState");
		virtual void entry(GameObject* player);
		virtual CState*  handleInput(GameObject* player, Grid& grid, const sf::Event& event);
		virtual CState* update(GameObject* player, sf::Time dt, Grid& grid);

		std::string getName();
};