#pragma once

#include <SFML/Graphics.hpp>
class GameObject;

class SpriteAnim
{

public:
	
	enum Status
	{
		RUNNING,
		SUCCESS,
		FAILURE,
		STOPPED,
		RESTARTED
	};
	
	
	SpriteAnim();
	SpriteAnim(sf::IntRect rect, int numberFrames, int frameToHold, bool loop, float speed = 1, int startFrame = 0, int frameToAllowNextAttack = -1 );
	int run(GameObject& player);
	int run(sf::RectangleShape& sprite);
	void exit();
	bool isAnimDelayed();
	bool allowNextAttack(int frameNum);


	// time keeping
	sf::Time deltaTime;
	sf::Clock deltaClock;
	sf::Time timeSinceUpdate;

	// frame variables
	int startingFrame;
	int currentFrame;
	int numFrames;
	int mFrameToHold;
	int mFrameToAllowNextAttack;

	bool mLoop;
	float playSpeed;
	float oldPlaySpeed;
	float slashDelaySpeed;	
	float timer;
	bool done;
	const sf::IntRect textureRect;


};