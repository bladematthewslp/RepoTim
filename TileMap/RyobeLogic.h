#pragma once

#include "LogicComponent.h"
#include "RyobeRender.h"
#include "Helper.h"

class RyobeLogic : public LogicComponent
{
	GameObject*					lightning;
	GameObject*					player;
	int							mDirection;
	sf::Vector2f				mVelocity;

	bool						mIsUntouchable;
	
	int							mHealth;
	GameObject*					mHealthBar;

	int							mMaxBarWidth;
	int							mMaxRectWidth;
	
	int							mHealthBarWidth;
	int							mHealthBarHeight;
	
	bool						mIsHit;
	int							mHitCounter;
	std::map<DamageType, int>	mDamageTable;
public:
	RyobeLogic(GameObject* gameObject);


	void			update(Grid& grid);
	
	bool			isUntouchable();

	GameObject*		getHealthBar();
	void			hit(GameObject* character, Attacks::Name);
	void			move(sf::Vector2f& vel);
	void			move(float x, float y);
	void			setVelocity(sf::Vector2f vel);
	void			setVelocity(float x, float y);
	void			setVelocityX(float x);
	void			setVelocityY(float y);
	sf::Vector2f	getVelocity();
	int				getHealth();

	int				getDirection();
	void			updateDirection();

	

};