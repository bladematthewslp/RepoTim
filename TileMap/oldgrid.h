#include "Grid.h"
#include <iostream>

std::array<std::array<int, 18>, 18> worldGrid = {{ 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,1,0,1,0,1,1,0,0,0,0,0,0,0,0},
					{0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0},
					{1,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0},
					{1,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0},
					{0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0},
				}}; 
Grid::Grid() : tileSize(32), playerPosition(), playerLanded(false)
{
	for(int i = 0; i < worldGrid.size(); i++)
	{
		for(int j = 0; j < worldGrid[0].size(); j++)
		{
			if(worldGrid[j][i] == 1)
			{
				mGrid[i][j] = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(32,32) )).release();
				mGrid[i][j]->setPosition(i*tileSize, j*tileSize);
				mGrid[i][j]->setFillColor(sf::Color::Red);
			}
		}
	}
	//this->mGrid = worldGrid;
}

bool Grid::checkCollision(Player& player, sf::Vector2f pos)
{
	playerPosition.x, playerPosition.y = 0;
	playerLanded = false;

	pos.x = (int)pos.x / tileSize;
	pos.y = (int)pos.y / tileSize;
	


	//if(mGrid[pos.y][pos.x] == 1)
	{
		//std::cout << pos.y << std::endl;
		//return true;
	}
	/*
	int playerGridPositionX = (player.getPosition().x) / tileSize;
//	int playerGridPositionY = (player.getPosition().y + 32) / tileSize;
	int playerGridPositionY = (player.getPosition().y + 10) / tileSize;
	if(playerGridPositionY >= 18)
		return true;

	if(mGrid[playerGridPositionY][playerGridPositionX] == 1)
	{
		//float positionOffset = playerGridPositionY * tileSize - (player.getLocalBounds().height/2);
		float positionOffset = playerGridPositionY * tileSize - (player.getLocalBounds().height/2);
		playerPosition.y = positionOffset;
		playerLanded = true;
		return true;
	}

	playerGridPositionX = (player.getPosition().x) / tileSize;
//	playerGridPositionY = (player.getPosition().y + 32) / tileSize;
	playerGridPositionY = (player.getPosition().y - 10) / tileSize;

	if(mGrid[playerGridPositionY][playerGridPositionX] == 1)
	{
		//float positionOffset = playerGridPositionY * tileSize - (player.getLocalBounds().height/2);
		//float positionOffset = playerGridPositionY * tileSize + (tileSize*2);// + (player.getLocalBounds().height/2);
		playerPosition.y = player.getPosition().y;
		player.setVelocity(sf::Vector2f(player.getVelocity().x, 0));//-player.getVelocity().y * 0.25));
		
		return true;
	}


	*/  
	return false;
	
}

void Grid::draw(sf::RenderWindow& window)
{
	for(int i = 0; i < worldGrid.size(); i++)
	{
		for(int j = 0; j < worldGrid[0].size(); j++)
		{
			if(worldGrid[j][i] == 1)
			{
				window.draw(*mGrid[i][j]);
				//mGrid[i][j]->draw(window);
			//	mGrid[i][j] = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(30,30) )).release();
				//mGrid[i][j]->setPosition(i*tileSize, j*tileSize);
			}
		}
	}

}





















