#include "TitleScene.h"

#include <iostream>


TitleScene::TitleScene(SceneStack& stack, Context context)
	: Scene(stack, context)
{
	mFont.loadFromFile("Sansation.ttf");

	mBackgroundSprite.setFillColor(sf::Color(0,0,0,155));
	mBackgroundSprite.setSize(sf::Vector2f(context.window->getSize().x, context.window->getSize().y));//sf::Vector2f(100,100));

	mText.setFont(mFont);
	
	mText.setString("Name of game here");
	mText.setPosition(50,50);//context.window->getView().getSize() / 2.f);
	
	mBackgroundSprite.setPosition(0,0);

}
bool TitleScene::handleEvent(sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(Scenes::Game);
	}
	
	return true;
}

bool TitleScene::handleInput(sf::Event& event)
{
	return true;
}

bool TitleScene::update(sf::Time dt)
{
	
	
	return true;
}
void TitleScene::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	window.draw(mBackgroundSprite);
	window.draw(mText);
}