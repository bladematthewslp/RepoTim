#include "Grid.h"
#include "GameObject.h"
#include "PlayerLogic.h"
#include "RenderComponent.h"
#include <iostream>

extern sf::RectangleShape* bBox;
std::array<std::array<int, 36>, 36> worldGrid = {{ 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				}}; 
Grid::Grid() : tileSize(32), playerPosition(), playerLanded(false)
{
	sf::RectangleShape block(sf::Vector2f(32,32));
	GameObjectDesc tile("Grid Block", block, Layer::Background, ComponentType::RenderComponent, nullptr);
	
	for(int i = 0; i < worldGrid.size(); i++)
	{
		for(int j = 0; j < worldGrid[0].size(); j++)
		{
			if(worldGrid[j][i] == 1)
			{
				mGrid[i][j] = std::unique_ptr<GameObject>(new GameObject(tile)).release();//sf::RectangleShape(sf::Vector2f(32,32)), ComponentType::RenderComponent,"Grid Block")).release();
				//mGrid[i][j] = std::unique_ptr<GameObject>(new GameObject(sf::RectangleShape(sf::Vector2f(32,32)), ComponentType::RenderComponent,"Grid Block")).release();
				//mGrid[i][j] = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(32,32) )).release();
				mGrid[i][j]->setPosition(i*tileSize, j*tileSize);
				
				mGrid[i][j]->getRenderComponent()->setFillColor(sf::Color::Red);
				//mGrid[i][j]->setFillColor(sf::Color::Red);
			}
			else
				mGrid[i][j] = nullptr;

		}
	}


	playerPosition.y = 0;
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
							block->setFillColor(sf::Color::Blue);
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



