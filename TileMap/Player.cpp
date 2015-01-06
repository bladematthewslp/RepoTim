#include "Player.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <set>
#include "Foreach.hpp"
#include "PlayerAttacks.h"
#include <Windows.h>
bool validKey(sf::Keyboard::Key key)
{
	switch(key)
	{
	case sf::Keyboard::Right:
	case sf::Keyboard::Left:
	case sf::Keyboard::Up:
	case sf::Keyboard::Down:
		PostQuitMessage(0);
		return true;
	}

	return false;
}

sf::Time deltaTime = sf::seconds(1.0f/60.0f);
Player::Player(GameObject* gameObject)
	: RenderComponent(gameObject),
	mState(nullptr)
	//, mSprite(sf::Vector2f(100,100))
	, mSprite(sf::Vector2f(400,400))
	, mVelocity(0.0f, 0.0f)
	, spriteClock()
	, mDirection(Direction::Right)
	, playerBBox(sf::Vector2f(mSprite.getGlobalBounds().width/4,mSprite.getGlobalBounds().height/4))
	, keyQueue()
{
	mSprite.setOrigin(mSprite.getLocalBounds().width/2, mSprite.getLocalBounds().height/2);
	mSprite.setPosition(150,(32*16) - mSprite.getLocalBounds().height/8);
	mPlayerImage.loadFromFile("Sprites/SpriteSheet_new.png");
	mPlayerImage.createMaskFromColor(sf::Color(0,128,0), 1);
	mPlayerTexture.loadFromImage(mPlayerImage);
	mSprite.setTexture(&mPlayerTexture);
	mSprite.setTextureRect(sf::IntRect(0,0, 200,200));
	spriteTimer = 0;
	
	
	playerBBox.setPosition(mSprite.getPosition().x, mSprite.getPosition().y);// + mSprite.getGlobalBounds().height/2);
	playerBBox.setOrigin(playerBBox.getLocalBounds().width/2, playerBBox.getLocalBounds().height/2);

	slashNumber = -1;

	init();
	

}


void Player::init()
{
	std::unique_ptr<PlayerState> state(new StandingState() );
	mState = state.release();

	registerAttacks();

}



void Player::update(Grid* grid, const sf::Event& event, sf::Time dt)
{
	//manageKeyQueue();
	
	// call handleInput on current state
	PlayerState* state = mState->handleInput(this, grid, event);

	// if input caused state to change, update Player class's state variable
	if(state != mState)
	{
		mState = state;
	}

	// call update on current state
	PlayerState* newState = mState->update(this, dt, grid);

	//if update caused state to change, update Player class's state variable
	if(newState != mState)
	{
		mState = newState;
	}
}

sf::RectangleShape& Player::getSprite()
{
	return mSprite;
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(mSprite);
}

sf::Vector2f Player::getPosition() const
{
	return mSprite.getPosition();
}


sf::Vector2f Player::getVelocity()
{
	return mVelocity;
}

void Player::setVelocity(sf::Vector2f vel)
{
	mVelocity = vel;
}

void Player::setPosition(sf::Vector2f pos)
{
	mSprite.setPosition(pos);
}

float Player::getRunningSpeed()
{
	return 5.0f;

}

void Player::setVelocityX(float x)
{
	mVelocity.x = x;
}

void Player::setVelocityY(float y)
{
	mVelocity.y = y;
}


void Player::updateDirection(int dir)
{
	if(mDirection != dir)
	{
		mDirection = dir;
		mSprite.setScale(-mSprite.getScale().x, mSprite.getScale().y);
	}
	
}

void Player::move(sf::Vector2f dir)
{
	mSprite.move(dir * 50.0f * deltaTime.asSeconds() );
	//playerBBox.setPosition(mSprite.getPosition().x, mSprite.getPosition().y + mSprite.getGlobalBounds().height/4);
	playerBBox.setPosition(mSprite.getPosition().x, mSprite.getPosition().y);
}


void Player::move(float x, float y)
{
	sf::Vector2f dir(x,y);
	mSprite.move(dir * 50.0f * deltaTime.asSeconds());
	playerBBox.setPosition(mSprite.getPosition().x, mSprite.getPosition().y);
}

unsigned int Player::getDirection()
{
	return mDirection;
}

void Player::handleInput(const sf::Event& event, sf::RenderWindow& window, Grid* grid)
{
	if(event.type == event.KeyPressed)
	{
		// check if key is a valid directional key
		sf::Keyboard::Key key = event.key.code;
		if(validKey(key) == true)
		{
			// if so, push the key in the keyQueue, removing the oldest key if queue is full
			if(keyQueue.size() == 2)
			{
				keyQueue.pop();
			}
			keyQueue.push(key);
		}
		//if(key == sf::Keyboard::Space)
		{
			mState->handleInput(this, grid, event);
		}
	}
}


std::queue<sf::Keyboard::Key>& Player::getKeyQueue()
{
	return keyQueue;
}


void Player::clearKeyQueue()
{
	if(keyQueue.size() != 0 )
	{
		while(keyQueue.size() != 0)
			keyQueue.pop();
	}
}

void Player::setTextureRect(sf::IntRect rect)
{
	mSprite.setTextureRect(rect);
}

void Player::registerAttacks()
{
	std::vector<sf::Keyboard::Key> slash1;
	slash1.push_back(sf::Keyboard::Down), slash1.push_back(sf::Keyboard::Right);
	//auto p = std::make_pair(slash1, Attack::slash1);
	
	mKeyActionBinding.insert(std::make_pair(slash1, Attack::slash1));
	
	slashOne = std::unique_ptr<PlayerAttack>(new PlayerAttack(sf::IntRect(200, 800, 200, 200), 7, 4)).release();
	slashTwo = std::unique_ptr<PlayerAttack>(new PlayerAttack(sf::IntRect(200, 1000, 200, 200), 7, 4)).release();
	slashThree = std::unique_ptr<PlayerAttack>(new PlayerAttack(sf::IntRect(200, 1200, 200, 200), 7, 5)).release();
	//Command slashOne;
	//slashOne.setAction(slash_one);
	//slashOne.action = [&] (Player* player) { std::cout << "COMMAND WORKS!!!" << std::endl; } ;
	//auto f = std::make_pair(Attack::slash1, slashOne);
	mActionCommandBinding.insert(std::make_pair(Attack::slash1, slashOne));
	
	std::vector<sf::Keyboard::Key> slash2;
	slash2.push_back(sf::Keyboard::Right), slash2.push_back(sf::Keyboard::Down);

	auto m = std::make_pair(slash2, Attack::slash2);
	mKeyActionBinding.insert(m);
	auto c = std::make_pair(Attack::slash2, slashTwo);
	mActionCommandBinding.insert(c);

	std::vector<sf::Keyboard::Key> slash3;
	slash3.push_back(sf::Keyboard::Right), slash3.push_back(sf::Keyboard::Right);
	mKeyActionBinding.insert(std::make_pair(slash3, Attack::slash3));
	mActionCommandBinding.insert(std::make_pair(Attack::slash3,slashThree));
}

void Player::manageKeyQueue()
{
	static int keyTimer = 0;
	if(keyQueue.size() != 0)
	{
	std::cout << keyQueue.front();
		if(keyQueue.size() == 2)
			std::cout << "," << keyQueue.back();
		std::cout << std::endl;
	}
	keyTimer++;
	if(keyTimer == 60)
	{
		if(keyQueue.size() != 0)
			keyQueue.pop();
			keyTimer = 0;
	}
}