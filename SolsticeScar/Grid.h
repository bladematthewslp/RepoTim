#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "RenderComponent.h"
//#include "Player.h"

class Player;
class GameObject;
class BoxColliderComponent;
class PlayerLogic;

struct Maps
{
	static std::string Cavern;
	static std::string Woods;
};

struct Grid
{
	std::map<int, Textures::ID>							mTileTable;


	sf::Vector2f										playerPosition;
	std::array<std::array<GameObject*, 160>, 160> mGrid;
	unsigned int										tileSize;
	bool												playerLanded;
	void												draw(sf::RenderWindow& window);

	Grid(std::string filename);

	sf::Image											mImage;
	sf::Texture											mTexture;
	//bool												checkCollision(Player& player, sf::Vector2f pos);
	bool												checkCollisionUnderPlayer(GameObject* player);
	bool												checkCollisionAbovePlayer(GameObject* player);
	bool												checkCollisionPlayerRight(GameObject* player);
	bool												checkCollisionPlayerLeft(GameObject* player);
	bool												checkWalkingOnTile(GameObject* player);
	float												getTileUnderPlayer(GameObject* player);
	bool												checkCollisionRight(BoxColliderComponent* collider);
	bool												checkCollisionLeft(BoxColliderComponent* collider);
	bool												checkCollisionAbove(BoxColliderComponent* collider);
	bool												checkCollisionBelow(BoxColliderComponent* collider);
	std::vector<std::array<int, 2>>							checkCellsOccupied(BoxColliderComponent* collider);
	bool												checkLeft(BoxColliderComponent* collider);

	Textures::ID										getTileTexture( int tile );

};