#include <iostream>
#include "Game.h"
#include <fstream>
#include <cctype>
#include <string>
//#include <sstream>





int main()
{
	
	/*
	std::ifstream openfile("Map1.txt");

	sf::Texture tileTexture;
	sf::Sprite tiles;

	sf::Vector2i map[100][100];
	sf::Vector2i loadCounter = sf::Vector2i(0,0);

	if(openfile.is_open() )
	{
		std::string tileLocation;
		openfile >> tileLocation;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture);
		while(!openfile.eof() )
		{
			std::string str;
			openfile >> str;
			char x = str[0], y = str[2];
			if(! isdigit(x) || !isdigit(y) )
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
			else
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');

			if(openfile.peek() == '\n')
			{
				loadCounter.x = 0;
				loadCounter.y++;
			}
			else
				loadCounter.x++;
		}
		loadCounter.y ++;

	}

	*/
	

	Game game;
	game.run();
	


	

}

