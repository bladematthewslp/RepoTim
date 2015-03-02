#include "GameScene.h"
#include "SceneStack.h"
#include "System.h"
#include <iostream>
#include "ResourceHolder.h"

GameScene::GameScene(SceneStack& stack, Context context)
	: Scene(stack, stack.mContext)
	, mShape()

{
	std::cout << "Game scene context = " << &stack.mContext << std::endl;
	mShape.setSize(sf::Vector2f(100,100));
	mShape.setFillColor(sf::Color(187, 88, 93, 255));
	mShape.setPosition(50,50);
	
	mWorld = std::unique_ptr<World>(new World(stack.mContext)).release();
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

		

		mWorld->handleEvent(window, event);
	//}
	return true;
}

bool GameScene::handleInput(sf::Event& event)
{
	mWorld->handleInput(event);
	return true;
}
bool GameScene::update(sf::Time dt)
{
	if(mWorld->update(dt) == false)
	{
		requestStackPop();
		requestStackPush(Scenes::Title);
	}
	return true;
}

void GameScene::draw()
{
	sf::RenderWindow& window = *getContext().window;
	mWorld->draw(window);
	//window.draw(mShape);

}