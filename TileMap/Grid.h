#pragma once

#include <SFML/Graphics.hpp>
#include <array>
//#include "Player.h"

class Player;
class GameObject;
class PlayerLogic;
struct Grid
{
	sf::Vector2f										playerPosition;
	std::array<std::array<GameObject*, 36>, 36> mGrid;
	unsigned int										tileSize;
	bool												playerLanded;
	void												draw(sf::RenderWindow& window);
	Grid();
	
	//bool												checkCollision(Player& player, sf::Vector2f pos);
	bool												checkCollisionUnderPlayer(GameObject* player);
	bool												checkCollisionAbovePlayer(GameObject* player);
	bool												checkCollisionPlayerRight(GameObject* player);
	bool												checkCollisionPlayerLeft(GameObject* player);
	bool												checkWalkingOnTile(GameObject* player);
	float												getTileUnderPlayer(GameObject* player);

};