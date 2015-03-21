#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "GameObject.h"
#include "Scene.h"
#include "Helper.h"

#include "HealthBarLogic.h"
#include "GUIRedOrbLogic.h"
#include "GUIRedOrbRender.h"
#include "NinjaGameObject.h"
#include "NinjaLogic.h"
#include "RyobeGameObject.h"
#include "PlayerRender.h"
#include "PlayerLogic.h"
#include "PlayerInput.h"
#include "PlayerBoxCollider.h"
#include "BackgroundGameObject.h"


#include "System.h"

#include <iostream>
#include <vector>




class World
{
protected:
	friend class GameScene;
	
	enum Status
	{
		PLAYING,
		PAUSED,
		PLAYER_WON,
		PLAYER_LOST,
		
	};

	// Background data
	GameObject*				mForeground[4];
	GameObject*				mBackground[5];

	// World characters
	GameObject*				mPlayer;

	// Player GUI data
	GameObject*				mHealthBar;
	GameObject*				GUIRedOrb;
	GameObject*				block;

	// world view data
	sf::Vector2f			mLookAtPoint;
	bool					scrollableWorld;							// toggle for if the world is still scrollable. Will be false when boss fight begins


	sf::RectangleShape		mFadeOutShape;								// shape used for world fade in/out

	float					timerToFadeOut;								// timer to fade out


	// private functions
	void					fadeIn();

	
	Scene::Context*			mContext;
public:

	typedef std::unique_ptr<World> Ptr;

	World(Scene::Context& context );
	
	virtual void			init();
	virtual bool			handleEvent(sf::RenderWindow& window,sf::Event& event);
	virtual bool			handleInput(sf::Event& event);

	virtual unsigned int	update(sf::Time dt) = 0;
	virtual void			draw(sf::RenderWindow& window);
	virtual void			destroyGameObjectsOutsideView();
	virtual void			updateCamera();

	virtual void			restartWorld();
	virtual void			cleanupWorld();

	

	sf::RenderWindow&		mWindow;
	sf::View				mWorldView;
	sf::FloatRect			mWorldBounds;
	unsigned int			mWorldWidth;
	unsigned int			mWorldHeight;
	Grid*					mGrid;
};