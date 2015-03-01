

#include <iostream>
#include "Game.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "Scene.h"
#include <array>

const sf::Time TimePerFrame = sf::seconds(1.0f/60.0f);


Game::Game() 
	: mWindow(sf::VideoMode(1024, 720,32), "TileMap")
	, worldWidth(1024)
	, worldHeight(720)
	, mWorldBounds(0.0f, 0.0f, 1024.f, 720.f)
	, mSceneStack(Scene::Context(mWindow))
{
	sf::ContextSettings settings = mWindow.getSettings();
	std::cout << settings.majorVersion << "." << settings.minorVersion << std::endl;
	sf::VideoMode videoMode;
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setPosition(sf::Vector2i(128, 0));
	registerScenes();
	mSceneStack.pushScene(Scenes::Title);

}


void Game::init()
{
	
}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
		
	while(mWindow.isOpen())
	{
		
			sf::Event event;
			
			timeSinceLastUpdate += clock.restart();
			while(timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				handleEvent(event);
				handleInput(event);
				update(TimePerFrame);
				
				if(mSceneStack.isEmpty())
					mWindow.close();
			}
		
			render();
	}
}

void Game::handleEvent(sf::Event& event)
{
	
	while(mWindow.pollEvent(event))
	{
		
		mSceneStack.handleEvent(event);

		if(event.type == sf::Event::Closed)
			mWindow.close();
		
	}
}

void Game::handleInput(sf::Event& event)
{
	mSceneStack.handleInput(event);
}
void Game::update(sf::Time dt)
{
	mSceneStack.update(dt);
}
void Game::render()
{
	mWindow.clear(sf::Color(0,0,0));
	
	mSceneStack.draw();
	
	mWindow.display();
	
}

void Game::registerScenes()
{
	mSceneStack.registerScene<TitleScene>(Scenes::Title);
	mSceneStack.registerScene<GameScene>(Scenes::Game);
	mSceneStack.registerScene<PauseScene>(Scenes::Pause);
}



