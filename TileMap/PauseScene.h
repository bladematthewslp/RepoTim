#pragma once

#include <SFML\Graphics.hpp>
#include "Scene.h"

class PauseScene : public Scene
{
	sf::RectangleShape		mShape;
public:
	PauseScene(SceneStack& stack, Context context);
	bool			handleEvent(sf::Event& event);
	bool			update(sf::Time dt);
	void			draw();

};