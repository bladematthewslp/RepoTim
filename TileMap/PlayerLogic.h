#pragma once

#include "LogicComponent.h"
#include <queue>
#include <array>
#include <string>
#include "Helper.h"

class CState;
struct Grid;

class PlayerLogic : public LogicComponent
{
public:
	typedef std::array<sf::Keyboard::Key, 2> keyArray;
	typedef std::vector<sf::Keyboard::Key> KeyVector;
private:
	GameObject*						mHealthBar;
	GameObject*						mRedOrbsGUI;
	int								mHealth;
	int								mNumRedOrbs;
	sf::Vector2f					mVelocity;
	sf::Vector2f					mGravity;
	int								mDirection;
	bool							mIsGrounded;
	// a map/lookup table of matching keys to attack type
	std::multimap<std::vector<sf::Keyboard::Key>, std::string> mMoveList;

	// DAMAGE TABLE
	std::map<DamageType, int>		mDamageTable;
public:

	PlayerLogic(GameObject* mGameObject);
	void update(Grid& grid);
	
	void				setNewState(CState* newState);

	void				pickupRedOrb();
	void				pickupGreenOrb();

	bool				canAttackFromState();
	void				setHealth(int num);
	int					getHealth();

	void				setGrounded(bool grounded);
	bool				isGrounded();

	void				registerAttacks();
	void				manageKeyQueue();

	std::multimap<std::vector<sf::Keyboard::Key>, std::string>& getMoveList();

	void				hit(GameObject* otherCharacter, Attacks::Name attackName);

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

	int					getDirection();
	void				updateDirection(int dir);

	
	std::queue<sf::Keyboard::Key>&		getKeyQueue();
	void				clearKeyQueue();

	void				setTextureRect(sf::IntRect rect);
	
	
	sf::FloatRect		box;
	void				updateBox();


	GameObject*			playerObject;
	GameObject*			playerBBox;
	

	
};