#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

enum Status
{
	RUNNING,
	SUCCESS
};

class Player;

class PlayerAttack
{
public:
	PlayerAttack();
	PlayerAttack(sf::IntRect rect, int numberFrames, int frameToHold);
	int run(Player* player);
	void exit();


	// time keeping
	sf::Time deltaTime;
	sf::Clock deltaClock;
	sf::Time timeSinceUpdate;

	// frame variables
	int currentFrame;
	int numFrames;
	int mFrameToHold;


	float playSpeed;
	float oldPlaySpeed;
	float slashDelaySpeed;	
	float timer;

	const sf::IntRect textureRect;
	
};
