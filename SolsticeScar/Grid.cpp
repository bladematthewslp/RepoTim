#include "Grid.h"
#include "GameObject.h"
#include "PlayerLogic.h"

#include "BoxColliderComponent.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <array>

std::array<std::array<int, 160>, 160> worldGrid;



std::string Maps::Cavern	= "Map/Level2.csv";
std::string Maps::Woods		= "Map/map1.csv";


Grid::Grid(std::string filename, int _tileSize) 
	: tileSize(_tileSize), playerPosition(), playerLanded(false)
{
	

	mTileTable[1]	= Textures::TILE_BLANK;
	mTileTable[2]	= Textures::TILE_ROCK_WALL4;
	mTileTable[3]	= Textures::TILE_GROUND2;

	mTileTable[4]	= Textures::TILE_BRICK_WALL2_0_0;
	mTileTable[5]	= Textures::TILE_BRICK_WALL2_0_1;
	mTileTable[6]	= Textures::TILE_BRICK_WALL2_0_2;
	mTileTable[7]	= Textures::TILE_BRICK_WALL2_1_0;
	mTileTable[8]	= Textures::TILE_BRICK_WALL2_1_1;
	mTileTable[9]	= Textures::TILE_BRICK_WALL2_1_2;
	mTileTable[10]	= Textures::TILE_BRICK_WALL2_2_0;
	mTileTable[11]	= Textures::TILE_BRICK_WALL2_2_1;
	mTileTable[12]	= Textures::TILE_BRICK_WALL2_2_2;
	mTileTable[13]	= Textures::TILE_BRICK_WALL2_3_0;
	mTileTable[14]	= Textures::TILE_BRICK_WALL2_3_1;
	mTileTable[15]	= Textures::TILE_BRICK_WALL2_3_2;


	sf::RectangleShape block(sf::Vector2f(tileSize,tileSize));
	GameObjectDesc tile("Grid Block", block, Layer::Default, ComponentType::RenderComponent, nullptr);
	
	//std::cout << "\n" << "LOADING GRID FROM FILE" << std::endl;
	std::ifstream openfile(filename);
	//std::cerr << "Loading Grid: " << strerror(errno);
	
	int x = 0;
	int y = 0;
	if(openfile.is_open() )
	{
		std::string tileLocation;
		openfile >> tileLocation;
	
		while(!openfile.eof() )
		{
			std::string str;
			openfile >> str;
			
			std::string tileCode = "";

			// for each line in the file, 
			for(int i  = 0; i < str.size(); i++)
			{
				// if the current marker is not on a comma....
				if(str[i] != ',')
				{
					// ...push this character into the tileCode string
					tileCode.push_back(str[i]);

				}
				// if the current marker IS a comma...
				else
				{
					// if tileCode is not empty...
					if(tileCode != "")
					{
						// convert code to int and put in worldGrid
						worldGrid[y][x] = std::stoi(tileCode);
						x++;
						tileCode = "";
					}
				}
			}

			if(openfile.peek() == '\n')
			{
				x = 0;
				y++;
			}
		}
	}

	//std::cout << "\nFINISHED LOADING GRID FROM FILE \n";
	
	//std::cout << std::endl << "CREATING GRID FOR WORLD" << std::endl << std::endl;
	for(int i = 0; i < worldGrid.size(); i++)
	{
		for(int j = 0; j < worldGrid[0].size(); j++)
		{
			if(worldGrid[j][i] != 0)
			{
				mGrid[i][j] = std::unique_ptr<GameObject>(new GameObject(tile)).release();//sf::RectangleShape(sf::Vector2f(32,32)), ComponentType::RenderComponent,"Grid Block")).release();
				mGrid[i][j]->setPosition(i*tileSize, j*tileSize);
				Textures::ID tileID = getTileTexture( worldGrid[j][i] );
				mGrid[i][j]->getRenderComponent()->mSprite.setTexture(&RenderComponent::mTextureHolder.get(tileID));//mTexture);
				//mGrid[i][j]->getRenderComponent()->mIsEnabled = false;
				
				
			}
			else
				mGrid[i][j] = nullptr;

		}
	}

	
	playerPosition.y = 0;
}

Textures::ID	Grid::getTileTexture( int tile )
{
	
	return mTileTable[tile];

}
void Grid::draw(sf::RenderWindow& window)
{
	for(int i = 0; i < mGrid.size(); i++)
	{
		for(int j = 0; j < mGrid[0].size(); j++)
		{
			if(mGrid[i][j] != nullptr)
			{
				//window.draw(*mGrid[i][j]);
			}
		}
	}

}
/*
bool Grid::checkCollision(PlayerLogic& player, sf::Vector2f pos)
{
	sf::Vector2f bL(player.getPosition().x - player.getLocalBounds().width/2, player.getPosition().y + player.getLocalBounds().height/2);
	sf::Vector2f bR(player.getPosition().x + player.getLocalBounds().width/2, player.getPosition().y + player.getLocalBounds().height/2);
	//std::cout << bL.x << "," << bL.y << std::endl;
	playerPosition.x, playerPosition.y = 0;
	playerLanded = false;

	pos.x = (int)pos.x / tileSize;
	pos.y = (int)pos.y / tileSize;
	
	
	return false;
	
}
*/


bool Grid::checkCollisionUnderPlayer(GameObject* player)
{
	

	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	

	playerPosition.y = 0;
	float tileYPos = 0;
	//sf::FloatRect playerRect = player->getSprite().getGlobalBounds();
	sf::RectangleShape* playerRect = logic->playerBBox->getSprite();
	for(int i = 0; i < mGrid.size(); i++)
	{
		for(int j = 0; j < mGrid[0].size(); j++)
		{
			if(mGrid[i][j] != nullptr)
			{
				sf::FloatRect gridBlockBounds = mGrid[i][j]->getRenderComponent()->mSprite.getGlobalBounds();
				if(mGrid[i][j] != nullptr)// && gridBlockBounds.intersects(playerRect->getGlobalBounds()) )
				{
					sf::RectangleShape* block = mGrid[i][j]->getSprite();
					if(logic->box.intersects(block->getGlobalBounds()) )
					{
						if(logic->box.top + logic->box.height > block->getPosition().y)// && block->getPosition().y < logic->box.top + logic->box.height*1.4)//playerRect->getPosition().y + playerRect->getGlobalBounds().height/2 >= mGrid[i][j]->getPosition().y)// mGrid[i][j]->getGlobalBounds().top)
				
						{
							//block->setFillColor(sf::Color::Blue);
							playerPosition.y = (logic->box.top + logic->box.height) - block->getPosition().y ;//(playerRect->getPosition().y + playerRect->getGlobalBounds().height/2) - mGrid[i][j]->getPosition().y;// mGrid[i][j]->getGlobalBounds().top;
							return true;
						}
					}
				}
			}
		}
	}

}

bool Grid::checkCollisionAbovePlayer(GameObject* player)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	float tileYPos = 0;
	//sf::FloatRect playerRect = player->getSprite().getGlobalBounds();
	sf::RectangleShape* playerRect = logic->playerBBox->getSprite();
	
	//sf::FloatRect playerRect = bBox->getGlobalBounds();// player->getSprite().getGlobalBounds();
	for(int i = 0; i < mGrid.size(); i++)
	{
		for(int j = 0; j < mGrid[0].size(); j++)
		{
			if(mGrid[i][j] != nullptr )
			{
				sf::FloatRect gridBlockBounds = mGrid[i][j]->getRenderComponent()->mSprite.getGlobalBounds();
				sf::RectangleShape* block = mGrid[i][j]->getSprite();
				if(logic->box.intersects(block->getGlobalBounds()) )
				//if(gridBlockBounds.intersects(playerRect->getGlobalBounds()) )
				{
					//if(playerRect->getPosition().y - playerRect->getGlobalBounds().height/2 <= gridBlockBounds.top + gridBlockBounds.height)
					if(logic->box.top <= gridBlockBounds.top + gridBlockBounds.height)	
						return true;
				}
			}
		}
	}

}

bool Grid::checkCollisionPlayerRight(GameObject* player)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	float tileYPos = 0;
	//sf::FloatRect playerRect = player->getSprite().getGlobalBounds();
	//sf::RectangleShape playerRect = player->playerBBox;//bBox;//->getGlobalBounds();
	sf::RectangleShape* playerRect = logic->playerBBox->getSprite();
	for(int i = 0; i < mGrid.size(); i++)
	{
		for(int j = 0; j < mGrid[0].size(); j++)
		{
			if(mGrid[i][j] != nullptr)
			{
				sf::FloatRect gridBlockBounds = mGrid[i][j]->getRenderComponent()->mSprite.getGlobalBounds();
				sf::RectangleShape* block = mGrid[i][j]->getSprite();
				if(logic->box.intersects(block->getGlobalBounds()) )
				{
					if(logic->box.left + logic->box.width > block->getPosition().x  && block->getPosition().x > logic->box.left )//block->gridBlockBounds.left )
					{
						//block->setFillColor(sf::Color::Blue);
						//std::cout << "RIGHT " << logic->box.left + logic->box.width << std::endl;
						return true;
					}
				}
			}
		}
	}

}

bool Grid::checkCollisionPlayerLeft(GameObject* player)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	sf::FloatRect box;
	
	float tileYPos = 0;
	sf::RectangleShape* playerRect = logic->playerBBox->getSprite();
	//std::cout << (playerRect->getTransform() * sf::Vector2f()).x << std::endl;
	//sf::RectangleShape playerRect = player->playerBBox;
	for(int i = 0; i < mGrid.size(); i++)
	{
		for(int j = 0; j < mGrid[0].size(); j++)
		{
			if(mGrid[i][j] != nullptr)
			{
				sf::FloatRect gridBlockBounds = mGrid[i][j]->getRenderComponent()->mSprite.getGlobalBounds();
				sf::RectangleShape* block = mGrid[i][j]->getSprite();

//				if(block->getGlobalBounds().intersects(playerRect->getGlobalBounds()) )
				if(logic->box.intersects(block->getGlobalBounds()) )
				{
					//std::cout << "INTERSECTING" << std::endl;
					sf::Vector2f bBoxWorldPosition = (playerRect->getTransform() * sf::Vector2f());
					sf::Vector2f gridBlockPosition = (mGrid[i][j]->getSprite()->getTransform() * sf::Vector2f());
					if(logic->box.left < block->getPosition().x + block->getGlobalBounds().width && block->getPosition().x < logic->box.left )
					//if(playerRect->getPosition().x - playerRect->getGlobalBounds().width/2 < gridBlockBounds.left + gridBlockBounds.width )
					{
						//block->setFillColor(sf::Color::Blue);
						//std::cout << block->getPosition().x + block->getGlobalBounds().width << std::endl;
						return true;
					}
				}
			}
		}
	}

}

bool Grid::checkWalkingOnTile(GameObject* player)
{
	PlayerLogic* logic = dynamic_cast<PlayerLogic*>(player->mLogicComponent);
	
	sf::FloatRect blockRect = logic->box;
	blockRect.height += 5;
	for(int i = 0; i < mGrid.size(); i++)
	{
		for(int j = 0; j < mGrid[0].size(); j++)
		{
			if(mGrid[i][j] != nullptr )
			{
				sf::FloatRect gridBlockBounds = mGrid[i][j]->getRenderComponent()->mSprite.getGlobalBounds();
				sf::RectangleShape* block = mGrid[i][j]->getSprite();
				if(blockRect.intersects(block->getGlobalBounds()) )
				{
					if(blockRect.top +  blockRect.height > block->getGlobalBounds().top)
					{
					
						return true;
					}
				}
			}
		}
	}
	return false;

	/*
	sf::FloatRect blockRect = logic->box;
	blockRect.height += 5;
	for(int i = 0; i < mGrid.size(); i++)
	{
		for(int j = 0; j < mGrid[0].size(); j++)
		{
			if(mGrid[i][j] != nullptr )
			{
				sf::FloatRect gridBlockBounds = mGrid[i][j]->getRenderComponent()->mSprite.getGlobalBounds();
				sf::RectangleShape* block = mGrid[i][j]->getSprite();
				if(blockRect.intersects(block->getGlobalBounds()) )
				{
					if(blockRect.top +  blockRect.height > block->getGlobalBounds().top)
					{
					
						return true;
					}
				}
			}
		}
	}
	return false;

	*/
}

float Grid::getTileUnderPlayer(GameObject* player)
{

	sf::FloatRect playerRect = player->getSprite()->getGlobalBounds();
	playerRect.height += 10;
	sf::Vector2f pointToFind(player->getPosition().x, player->getPosition().y + player->getSprite()->getGlobalBounds().height/2 + 15);
	//std::cout << pointToFind.x << "," << pointToFind.y << std::endl;
	for(int i = 0; i < mGrid.size(); i++)
	{
		for(int j = 0; j < mGrid[0].size(); j++)
		{
			if(mGrid[i][j] != nullptr)
			{
				sf::FloatRect gridBlockBounds = mGrid[i][j]->getRenderComponent()->mSprite.getGlobalBounds();
				if(gridBlockBounds.intersects((playerRect) ))
				{
					return gridBlockBounds.top;
					//if(bBox->getPosition().y + testBox.height > mGrid[i][j]->getGlobalBounds().top)//player->getPosition().x - playerRect.width/2 < mGrid[i][j]->getGlobalBounds().left + mGrid[i][j]->getGlobalBounds().width )
					//{
					//	return true;
					//}
				}
			}
		}
	}
}


bool Grid::checkCollisionRight(BoxColliderComponent* collider)
{
	sf::RectangleShape* box = collider->getCollisionBox();
	sf::Vector2f topRight(box->getGlobalBounds().left + box->getGlobalBounds().width, box->getGlobalBounds().top);
	//std::cout << topRight.x << " , " << topRight.y << std::endl;
	int xPoint = topRight.x / tileSize;
	int yPoint = topRight.y / tileSize;
	//std::cout << xPoint << " , " << yPoint<< std::endl;
	if(xPoint >= 0 && yPoint >= 0)
	if(worldGrid[yPoint][xPoint] != 0)
	{
		return true;
	}

	sf::Vector2f bottomRight(box->getGlobalBounds().left + box->getGlobalBounds().width, box->getGlobalBounds().top + box->getGlobalBounds().height- 10);
	xPoint = bottomRight.x / tileSize;
	yPoint = bottomRight.y / tileSize;
	if(xPoint >= 0 && yPoint >= 0)
	{

		if(worldGrid[yPoint][xPoint] != 0)
		{
			return true;
		}
	}
	return false;
}

bool Grid::checkCollisionLeft(BoxColliderComponent* collider)
{
	sf::RectangleShape* box = collider->getCollisionBox();
	sf::Vector2f topLeft(box->getGlobalBounds().left, box->getGlobalBounds().top);

	int xPoint = topLeft.x / tileSize;
	int yPoint = topLeft.y / tileSize;

	if(xPoint >= 0 && yPoint >= 0)
	{
		if(worldGrid[yPoint][xPoint] != 0)
		{
			return true;
		}
	}
	sf::Vector2f bottomLeft(box->getGlobalBounds().left, box->getGlobalBounds().top + box->getGlobalBounds().height - 10);
	xPoint = bottomLeft.x / tileSize;
	yPoint = bottomLeft.y / tileSize;
	if(xPoint >= 0 && yPoint >= 0)
	{

		if(worldGrid[yPoint][xPoint] != 0)
		{
			return true;
		}
	}
	return false;
}

bool Grid::checkCollisionAbove(BoxColliderComponent* collider)
{
	sf::RectangleShape* box = collider->getCollisionBox();
	sf::Vector2f topLeft(box->getGlobalBounds().left, box->getGlobalBounds().top);

	int xPoint = topLeft.x / tileSize;
	int yPoint = topLeft.y / tileSize;

	if(xPoint >= 0 && yPoint >= 0)
	{
		if(worldGrid[yPoint][xPoint] != 0)
		{
			return true;
		}
	}

	sf::Vector2f topRight(box->getGlobalBounds().left + box->getGlobalBounds().width, box->getGlobalBounds().top);
	//std::cout << topRight.x << " , " << topRight.y << std::endl;
	xPoint = topRight.x / tileSize;
	yPoint = topRight.y / tileSize;
	//std::cout << xPoint << " , " << yPoint<< std::endl;
	if(xPoint >= 0 && yPoint >= 0)
	{
		if(worldGrid[yPoint][xPoint] != 0)
		{
			return true;
		}

	}
	return false;
}

bool Grid::checkCollisionBelow(BoxColliderComponent* collider)
{
	playerPosition.y = 0;
	sf::RectangleShape* box = collider->getCollisionBox();
	sf::Vector2f bottomLeft(box->getGlobalBounds().left, box->getGlobalBounds().top + box->getGlobalBounds().height);
	int xPoint = bottomLeft.x / tileSize;
	int yPoint = bottomLeft.y / tileSize;
	if(xPoint >= 0 && yPoint >= 0)
	{

		if(mGrid[xPoint][yPoint] != nullptr)// && worldGrid[yPoint][xPoint] == 1)
		{
			//std::cout << " BELOW - BOTTOM LEFT ! " << std::endl;
			playerPosition.y = (bottomLeft.y - mGrid[xPoint][yPoint]->getPosition().y);//   logic->box.top + logic->box.height) - block->getPosition().y ;
			return true;
		}
	}
	
	sf::Vector2f bottomRight(box->getGlobalBounds().left + box->getGlobalBounds().width, box->getGlobalBounds().top + box->getGlobalBounds().height);
	xPoint = bottomRight.x / tileSize;
	yPoint = bottomRight.y / tileSize;
	if(xPoint >= 0 && yPoint >= 0)
	{
		if(mGrid[xPoint][yPoint] != nullptr)
		{
			//std::cout << " BELOW - BOTTOM RIGHT ! " << std::endl;
			playerPosition.y = (bottomRight.y - mGrid[xPoint][yPoint]->getPosition().y);//   logic->box.top + logic->box.height) - block->getPosition().y ;
			return true;
		}
	}
	return false;
}

std::vector<std::array<int, 2>> Grid::checkCellsOccupied(BoxColliderComponent* collider)
{
	sf::RectangleShape* box = collider->getCollisionBox();
	std::vector<GameObject*> cells;
	
	std::vector<std::array<int, 2>> cells1;
	
	sf::Vector2f topLeft(box->getGlobalBounds().left, box->getGlobalBounds().top);
	sf::Vector2f topRight(box->getGlobalBounds().left + box->getGlobalBounds().width, box->getGlobalBounds().top);
	sf::Vector2f bottomLeft(box->getGlobalBounds().left, box->getGlobalBounds().top + box->getGlobalBounds().height);
	sf::Vector2f bottomRight(box->getGlobalBounds().left + box->getGlobalBounds().width, box->getGlobalBounds().top + box->getGlobalBounds().height);

	int startTopLeft = topLeft.y/tileSize;
	int endTopBottom = bottomRight.x/tileSize;
	
	if(startTopLeft < 0 || endTopBottom < 0)
		return cells1;
	int count = 0;
	for( int i = topLeft.y/tileSize; i < bottomRight.y/tileSize; i++)
	{
		for(int j = topLeft.x/tileSize; j < bottomRight.x/tileSize; j++)
		{
			std::array<int,2> cell;
			cell[0] = i;
			cell[1] = j;
			cells1.push_back(cell);
			cells.push_back(mGrid[i][j]);

			//std::cout << i << "," << j << std::endl;
			count++;
		}
	}
	for(int g = 0; g < cells1.size(); g++)
	{
		//std::cout << cells1[g].at(0) << "," << cells1[g].at(1) << std::endl;
	}
	//std::cout << count << std::endl;
	
	return cells1;

}

bool Grid::checkLeft(BoxColliderComponent* collider)
{
	std::vector<std::array<int, 2>> cells = collider->getOccupiedCells();
	if(cells.size() == 0)
		return false;
	/*
	GameObject* topLeft(*cells.begin());
	GameObject* bottomRight(*cells.end());
	topLeft->getPosition().x / 32;
	
	sf::Vector2f topLeft(box->getGlobalBounds().left, box->getGlobalBounds().top);
	sf::Vector2f topRight(box->getGlobalBounds().left + box->getGlobalBounds().width, box->getGlobalBounds().top);
	sf::Vector2f bottomLeft(box->getGlobalBounds().left, box->getGlobalBounds().top + box->getGlobalBounds().height);
	sf::Vector2f bottomRight(box->getGlobalBounds().left + box->getGlobalBounds().width, box->getGlobalBounds().top + box->getGlobalBounds().height);
	
	int startTopLeft = topLeft.y/32;
	int endTopBottom = bottomRight.x/32;
	*/
	int startX = cells[0].at(0);
	int startY = cells[0].at(1);
	int endX = cells[cells.size() - 1].at(0);

	for( int i = startY; i < cells[cells.size() - 1].at(1); i++)
	{
		if(mGrid[i][startX+2] != nullptr)
		{
			//std::cout << "LEFT checkleft" << std::endl;
			return true;
		}
	/*	for(int j = cells[0].at(0); j < endX; j++)
		{
			if(mGrid[i][j] != nullptr)
			
			
		}*/
	}
	

	return false;
}