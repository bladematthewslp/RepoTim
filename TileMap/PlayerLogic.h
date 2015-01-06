#pragma once

#include "LogicComponent.h"
#include <queue>

enum Direction
{
	Right = 1,
	Left = -1,
};

class PlayerState;
struct Grid;
class PlayerLogic : public LogicComponent
{
	

	sf::Vector2f					mVelocity;
	sf::Vector2f					mGravity;
	int								mDirection;
public:

	sf::FloatRect		box;
	void				updateBox();


	GameObject*			playerObject;
	GameObject*			playerBBox;
	
	PlayerLogic(GameObject* mGameObject);
	void update(Grid& grid);

	sf::Vector2f		getPosition() const;
	void				setPosition(sf::Vector2f pos);

	sf::FloatRect		getLocalBounds() const;
	sf::FloatRect		getGlobalBounds() const;

	sf::Vector2f		getVelocity();
	void				setVelocity(sf::Vector2f vel);
	void				setVelocityX(float x);
	void				setVelocityY(float y);

	float				getRunningSpeed();
	void				accelerate();

	void				move(sf::Vector2f dir);
	void				move(float x, float y);

	int		getDirection();
	void				updateDirection(int dir);

	
	std::queue<sf::Keyboard::Key>&		getKeyQueue();
	void				clearKeyQueue();

	void				setTextureRect(sf::IntRect rect);
	void				registerAttacks();
	void				manageKeyQueue();
};