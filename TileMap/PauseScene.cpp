#include "PauseScene.h"
#include "SceneStack.h"
#include <iostream>

PauseScene::PauseScene(SceneStack& stack, Context context)
	: Scene(stack, context)
	, mShape(sf::Vector2f(100,100))
{
	mShape.setFillColor(sf::Color::Magenta);
	sf::Vector2f viewOrigin;
	viewOrigin.x = getContext().window->getView().getCenter().x - getContext().window->getSize().x/2;
	viewOrigin.y = getContext().window->getView().getCenter().y - getContext().window->getSize().y/2;
	mShape.setPosition(viewOrigin + sf::Vector2f(300,300));
}

bool PauseScene::handleEvent(sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::BackSpace)
		{
			requestStackClear();
		}
		if(event.key.code == sf::Keyboard::Escape)
		{
			requestStackPop();
		}
	}
	return false;
}

bool PauseScene::handleInput(sf::Event& event)
{

	return true;
}

bool PauseScene::update(sf::Time dt)
{
	
	return false;
}

void PauseScene::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mShape);

}