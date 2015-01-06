#ifndef GAME_H_
#define GAME_H_
#include <SFML/Graphics.hpp>
//#include "Player.h"
#include "Grid.h"
#include <array>
#include "GameObject.h"
#include "GameObjectManager.h"
//#include "System.h"
//#include "PlayerObject.h"

class GameObjectManager;
class Game
{
	public:
							Game();
		void				init();
		void				run();
		void				render();
		void				handleInput(sf::Event& event);
		Player&				getPlayer();
		GameObjectManager	mGameObjectManager;
	private:
		void					drawGrid(sf::RenderWindow& window);
		void					processInput();
		
		sf::RenderWindow		mWindow;
		sf::FloatRect			mWorldBounds;
		
		unsigned int			worldWidth;
		unsigned int			worldHeight;
		//Player					mPlayer;
		GameObject				mPlayer;
		Grid					grid;
		//System					mSystem;
};


#endif // GAME_H_