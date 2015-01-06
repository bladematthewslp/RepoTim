#pragma once

#include <SFML/Graphics.hpp>

#include <vector>


//class Player;
struct Grid;
class Component;
class PlayerLogic;

class GameObject;
class PlayerState
{
	
	public:
		virtual void entry(GameObject* player);
		virtual PlayerState*  handleInput(GameObject* player, Grid& grid, const sf::Event& event);
		virtual PlayerState* update(GameObject* player, sf::Time dt, Grid& grid);
		
		std::vector<sf::Vector2f>	getJumpingSpriteSizes();
		std::vector<sf::IntRect>	getJumpingSpriteBounds();
};