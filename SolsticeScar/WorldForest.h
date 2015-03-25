#pragma once

#include "World.h"


class WorldForest : private World
{
	
	// Background data
	GameObject*				mForeground[4];
	GameObject*				mBackground[5];

	// World characters
	GameObject*				mPlayer;
	std::vector<GameObject*>	ninjaGameObjects;
	GameObject*				ryobeGameObject;

	// Player GUI data
	GameObject*				mHealthBar;
	GameObject*				GUIRedOrb;
	GameObject*				block;

	// world view data
	//sf::Vector2f			mLookAtPoint;
	bool					scrollableWorld;							// toggle for if the world is still scrollable. Will be false when boss fight begins

	// boss fight variables
	GameObject*				lightningWallLeft;
	GameObject*				lightningWallRight;
	float					xPositionBossFightStart;					// location where player must be for boss fight to begin
	bool					playerReachedBossFightLocation;				// check for if player has reached the boss fight location
	bool					bossFightStarted;							// check if the boss fight has started
	float					timerToBeginBattle;							// timer to start the boss battle
	bool					startTimerToBeginBattle;					// check for if the boss battle timer has started

	
	float					timerToStartPlayerWinPose;					// timer for player's win pose


	//sf::RectangleShape		mFadeOutShape;								// shape used for world fade in/out

	// data to use for world restart or world completion
	bool					playerDefeated;								// check if player is dead
	bool					bossDefeated;								// check for if the boss is defeated
	float					timerToFadeOut;								// timer to fade out


	// private functions
	//void					fadeIn();

	
	
public:



	WorldForest(Scene::Context& context );
	
	virtual void					init();
	//virtual bool					handleEvent(sf::RenderWindow& window,sf::Event& event);
	//virtual bool					handleInput(sf::Event& event);

	virtual unsigned int			update(sf::Time dt);
	//virtual void					draw(sf::RenderWindow& window);
	//virtual void					destroyGameObjectsOutsideView();
	virtual void					updateCamera();

	virtual void					restartWorld();
	//virtual void					cleanupWorld();


	Grid*							mGrid;
};