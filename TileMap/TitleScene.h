#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"


class TitleScene : public Scene
{
	sf::RectangleShape		mBackgroundSprite;
	sf::Text		mText;
	sf::Font		mFont;
public:
					TitleScene(SceneStack& stack, Context context);
	virtual bool	handleEvent(sf::Event& event);
	virtual bool	handleInput(sf::Event& event);

	virtual bool	update(sf::Time dt);
	virtual void	draw();
	
};