#include "GameScene.h"
#include "SceneStack.h"
#include "WorldWoods.h"
#include "WorldForest.h"
#include "System.h"
#include <iostream>
#include "ResourceHolder.h"

GameScene::GameScene(SceneStack& stack, Context& context)
	: Scene(stack, stack.mContext)
	, mShape()

{


	//std::cout << "Game scene context = " << &stack.mContext << std::endl;
	mShape.setSize(sf::Vector2f(100,100));
	mShape.setFillColor(sf::Color(187, 88, 93, 255));
	mShape.setPosition(50,50);
	
	registerWorld<WorldForest>(Worlds::Forest);
	registerWorld<WorldWoods>(Worlds::Woods);
	mCurrentWorld = createWorld(mWorlds.front());
	
	//mWorld = std::unique_ptr<World>(new World(stack.mContext)).release();
}

bool GameScene::handleEvent(sf::Event& event)
{
	sf::RenderWindow& window = *getContext().window;
//	while(window.pollEvent(event))
	//{
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Escape)
			{
				requestStackPush(Scenes::Pause);
				return false;
			}
		}

		

		mCurrentWorld->handleEvent(window, event);
	//}
	return true;
}

bool GameScene::handleInput(sf::Event& event)
{
	mCurrentWorld->handleInput(event);
	return true;
}
bool GameScene::update(sf::Time dt)
{
	switch( mCurrentWorld->update(dt) )
	{
		case World::Status::PLAYING:
		{
			break;
		}
		case World::Status::PLAYER_WON:
		{
			mWorlds.erase(mWorlds.begin() );
			if(mWorlds.size() == 0)
			{
				requestStackPop();
				requestStackPush(Scenes::Title);
			}
			else
			{
				mCurrentWorld = createWorld(mWorlds.front());
			}
			break;
		}
		case World::Status::PLAYER_LOST:
		{
			break;
		}
		case World::Status::PAUSED:
		{
			break;
		}
	}
	return true;
}

void GameScene::draw()
{
	sf::RenderWindow& window = *getContext().window;
	mCurrentWorld->draw(window);

}

World::Ptr GameScene::createWorld(Worlds::ID worldID)
{
	auto found = mWorldFactories.find(worldID);
	
	assert(found != mWorldFactories.end());
	return found->second();

}