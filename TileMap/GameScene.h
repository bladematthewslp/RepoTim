#pragma once

#include <SFML\Graphics.hpp>
#include "Scene.h"
#include "World.h"

class SceneStack;

class GameScene : public Scene
{
	sf::RectangleShape	mShape;
	World*				mWorld;
public:
	GameScene(SceneStack& stack, Context context);

	bool handleEvent(sf::Event& event);
	bool handleInput(sf::Event& event);

	bool update(sf::Time dt);
	void draw();

};