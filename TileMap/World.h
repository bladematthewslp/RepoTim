#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GameObject.h"
#include <vector>



class World
{
	GameObject*				mBackground[5];
	GameObject*				mPlayer;
	sf::Vector2f			mLookAtPoint;
	GameObject*				mHealthBar;
	GameObject*				GUIRedOrb;
	GameObject*				block;

	// world enemies
	std::vector<GameObject*>	ninjaGameObjects;
	GameObject*				ryobeGameObject;

	// boss fight variables
	GameObject*				lightningWallLeft;
	GameObject*				lightningWallRight;
	float					xPositionBossFightStart;
	bool					bossFightStarted;
	bool					scrollableWorld;
	float					timerToBeginBattle;
	bool					startTimerToBeginBattle;

public:
	World(sf::RenderWindow& window);

	bool					handleEvent(sf::RenderWindow& window,sf::Event& event);
	bool					handleInput(sf::Event& event);

	bool					update(sf::Time dt);
	void					draw(sf::RenderWindow& window);
	void					destroyGameObjectsOutsideView();

	sf::RenderWindow&		mWindow;
	sf::View				mWorldView;
	sf::FloatRect			mWorldBounds;
	unsigned int			mWorldWidth;
	unsigned int			mWorldHeight;
	Grid*					mGrid;
};