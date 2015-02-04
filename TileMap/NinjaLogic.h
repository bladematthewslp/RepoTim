#pragma once

#include <SFML/Graphics.hpp>
#include "AttackType.h"
#include "LogicComponent.h"
#include "Helper.h"

struct Grid;
class CState;

class NinjaLogic : public LogicComponent
{
	
	CState*		mState;
	int			mDirection;
	int			mHealth;
	sf::Vector2f mVelocity;
	float		mRunningSpeed;
	std::map<DamageType, int>	mDamageTable;
	bool		mIsGrounded;
public:
	NinjaLogic(GameObject* mGameObject);
	void		update(Grid& grid);

	void		move(float x, float y);
	void		move(sf::Vector2f pos);

	void		setGrounded(bool flag);
	bool		isGrounded();
	GameObject* player;
	int			getDirection();
	void		updateDirection();
	int			getHealth();
	void		hit(GameObject* character, Attacks::Name attack);

	sf::Vector2f getVelocity();
	void		setVelocity(sf::Vector2f vel);
	void		setVelocity(float x, float y);
	void		setVelocityX(float num);
	void		setVelocityY(float num);

	float		getRunningSpeed();

};