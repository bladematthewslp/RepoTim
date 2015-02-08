#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GameObject.h"




class World
{
	GameObject*				mBackground[5];
	GameObject*				mPlayer;
	sf::Vector2f			mLookAtPoint;
	GameObject*				mHealthBar;
	GameObject*				GUIRedOrb;
	GameObject*				block;
public:
	World(sf::RenderWindow& window);

	bool					handleEvent(sf::RenderWindow& window,sf::Event& event);
	bool					handleInput(sf::Event& event);

	bool					update(sf::Time dt);
	void					draw(sf::RenderWindow& window);

	sf::RenderWindow&		mWindow;
	sf::View				mWorldView;
	sf::FloatRect			mWorldBounds;
	unsigned int			mWorldWidth;
	unsigned int			mWorldHeight;
	Grid*					mGrid;
};