#pragma once
//#include "PlayerAttacks.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "StandingState.h"
#include <array>
#include <queue>
#include <functional>
#include "LogicComponent.h"
#include "RenderComponent.h"


struct Grid;
class PlayerState;
class PlayerAttack;



enum Attack
{
	slash1,
	slash2,
	slash3
};

class Player : public RenderComponent
{
	
	sf::RectangleShape				mSprite;
	sf::Vector2f					mVelocity;
	sf::Vector2f					mGravity;
	PlayerState*					mState;
	sf::Image						mPlayerImage;
	sf::Texture						mPlayerTexture;
	sf::Sprite						mPlayerSprite;
	int								mDirection;
	std::queue<sf::Keyboard::Key>	keyQueue;

	PlayerAttack*					slashOne;
	PlayerAttack*					slashTwo;
	PlayerAttack*					slashThree;


public:
	int								slashNumber;
	std::map<std::vector<sf::Keyboard::Key>, int > mKeyActionBinding;
	std::map<int, PlayerAttack*>	mActionCommandBinding;
	sf::Clock						spriteClock;
	int								spriteTimer;

	sf::RectangleShape				playerBBox;


public:
						Player(GameObject*);
	void				init();
	void				update(Grid* grid, const sf::Event& event, sf::Time dt);
	void				draw(sf::RenderWindow& window);
	void				handleInput(const sf::Event& event, sf::RenderWindow& window, Grid* grid);
	
	sf::RectangleShape&	getSprite();

	sf::Vector2f		getPosition() const;
	void				setPosition(sf::Vector2f pos);

	sf::FloatRect		getLocalBounds() const { return mSprite.getLocalBounds(); };
	sf::FloatRect		getGlobalBounds() const { return mSprite.getGlobalBounds(); };

	sf::Vector2f		getVelocity();
	void				setVelocity(sf::Vector2f vel);
	void				setVelocityX(float x);
	void				setVelocityY(float y);

	float				getRunningSpeed();
	void				accelerate();

	void				move(sf::Vector2f dir);
	void				move(float x, float y);

	unsigned int		getDirection();
	void				updateDirection(int dir);

	
	std::queue<sf::Keyboard::Key>&		getKeyQueue();
	void				clearKeyQueue();

	void				setTextureRect(sf::IntRect rect);
	void				registerAttacks();
	void				manageKeyQueue();
};

